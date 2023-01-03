//
// Created by Never on 12/29/2022.
//
#include "../header/file.h"


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