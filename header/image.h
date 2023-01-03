//
// Created by Never on 12/29/2022.
//

#ifndef LAB5_IMAGE_H
#define LAB5_IMAGE_H

#include <stdint.h>
#include <stdbool.h>

struct image {
    uint64_t width, height;
    struct pixel* data;
};


struct __attribute__ ((packed)) pixel { uint8_t b, g, r;};

void free_img(struct image* img);
bool check_image(struct image img);
struct image create_img(uint32_t width, uint32_t height);
uint8_t missing_width(uint32_t width);
void sepia_c_inplace(struct image* img);
void sepia_asm_inplace(struct image* img);

#endif //LAB5_IMAGE_H
