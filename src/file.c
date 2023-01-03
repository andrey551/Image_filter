//
// Created by Never on 12/29/2022.
//
#include "file.h"


enum read_status from_bmp( FILE* in, struct image* img ) {

    struct bmp_header header = {0};

    if (!fread(&header, sizeof(struct bmp_header), 1, in))
        return READ_INVALID_HEADER;
    enum read_status valid_header = validate_header(header);
    if( valid_header != READ_OK) return valid_header;
    *img = create_img(header.biWidth, header.biHeight);
    if(!img->data) return READ_ERROR;
    for ( uint32_t i = 0; i < img->height; ++i ) {
        if(fread(img->data + img->width * i, sizeof(struct pixel), img->width, in) != img->width) {
            return READ_INVALID_BITS;
        }
        if(fseek( in, missing_width(img->width), SEEK_CUR )) {
            return READ_INVALID_BITS;
        }
    }

    if(!img) return READ_ERROR;
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img ) {

    struct bmp_header header = create_header(img->width, img->height);
    uint32_t pixel_missed = missing_width(img->width);

    if (!fwrite(&header, sizeof(struct bmp_header), 1, out)) {
        return WRITE_ERROR;
    }

    for (uint32_t i = 0; i < img->height; ++i) {
        if(fwrite(img->data + i * img->width,sizeof(struct pixel) * img->width,1,out) != 1) {
            return WRITE_ERROR;
        };
        uint32_t empty_pixel = 0;
        if(pixel_missed != 0) {
            if(!fwrite(&empty_pixel, pixel_missed, 1, out )) return WRITE_ERROR;
        }
    }

    return WRITE_OK;
}

struct bmp_header create_header(uint32_t width, uint32_t height) {
    return (struct bmp_header) {
            .bfType = BF_TYPE,
            .bfileSize = sizeof(struct bmp_header) + height * (PIXEL_SIZE * width + missing_width(width)),
            .bfReserved = BF_REVERSED,
            .bOffBits = B_OFF_BITS,
            .biSize = BI_SIZE,
            .biWidth = width,
            .biHeight = height,
            .biPlanes = BI_PLANES,
            .biBitCount = BI_BIT_COUNT,
            .biCompression = BI_COMPRESSION,
            .biSizeImage = height * (PIXEL_SIZE * width + missing_width(width)),
            .biXPelsPerMeter = BI_X_PELS_PER_METER,
            .biYPelsPerMeter = BI_Y_PELS_PER_METER,
            .biClrUsed = BI_CLR_USED,
            .biClrImportant = BI_CLR_IMPORTANT
    };
}

enum read_status validate_header(const struct bmp_header header) {
    if(header.bfType != BF_TYPE && header.bfType != 0x4349 &&header.bfType != 0x5450)
        return READ_INVALID_SIGNATURE;

    if(header.biBitCount != BI_BIT_COUNT) {
        return READ_INVALID_BITS;
    }

    return READ_OK;

}

void free_img(struct image* img) {
    if(img->data) {
        free(img->data);
        img->data = NULL;
    }
}

bool check_image(struct image img) {

    if(img.data) return true;
    return false;
}

struct image create_img(uint32_t width, uint32_t height) {
    return (struct image) {
            .width = width,
            .height = height,
            .data = malloc(width * height * sizeof(struct pixel))
    };
}

uint8_t missing_width(uint32_t width) {
    if(width % 4 == 0) return 0;
    return 4 - (width * 3 % 4);
}

static unsigned char sat( uint64_t x) {
    if (x < 256) return x; return 255;
}
static void sepia_one( struct pixel* const pixel ) {
    static const float c[3][3] = {
            { .393f, .769f, .189f },
            { .349f, .686f, .168f },
            { .272f, .543f, .131f } };
    struct pixel const old = *pixel;
    pixel->r = sat(
            old.r * c[0][0] + old.g * c[0][1] + old.b * c[0][2]
    );
    pixel->g = sat(
            old.r * c[1][0] + old.g * c[1][1] + old.b * c[1][2]
    );
    pixel->b = sat(
            old.r * c[2][0] + old.g * c[2][1] + old.b * c[2][2]
    );
}
void sepia_c_inplace( struct image* img ) {
    uint32_t x,y;
    for( y = 0; y < img->height; y++ )
        for( x = 0; x < img->width; x++ )
            sepia_one( img->data + y * img->width + x );
}

//extern void sepia_filter_asm(struct pixel* restrict);
//
//void sepia_asm_inplace(struct image* img) {
//    uint32_t iter = 0;
//    for(iter = 0; iter <= img->height * img->width; iter += 4) {
//        sepia_filter_asm(img->data + iter);
//    }
//}

void print_err(char msg[]) {
    if(!msg) {
        fprintf(stderr,"%s \n",  msg);
    }
}

void print_read_status(int st) {
    switch (st) {
        case READ_ERROR:
            print_err(SIGNATURE_ERROR);
            break;
        case READ_INVALID_SIGNATURE:
            print_err(READ_IMAGE_ERROR);
            break;
        case READ_INVALID_BITS:
            print_err(READ_HEADER_ERROR);
            break;
        default:
            printf(ALL_OK);
    };
}

void print_write_status(int st) {
    switch (st) {
        case WRITE_ERROR:
            print_err(WRITER_ERROR);
            break;
        default:
            printf(ALL_OK);
    };
}
int check_arguments(int num_of_argument) {
    if(num_of_argument != 3) {
        print_err(ARGUMENT_ERROR);
        return 0;
    }
    return 1;
}