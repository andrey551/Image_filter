//
// Created by Never on 12/29/2022.
//
#include "../header/image.h"
#include <stdlib.h>
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

extern void sepia_filter_asm(struct pixel* restrict);

void sepia_asm_inplace(struct image* img) {
    uint32_t iter = 0;
    for(iter = 0; iter <= img->height * img->width; iter += 4) {
        sepia_filter_asm(img->data + iter);
    }
}