//
// Created by Never on 12/29/2022.
//

#ifndef LAB5_HEADER_H
#define LAB5_HEADER_H

#include <stdint.h>
#include "stat.h"
#include "image.h"

#define BF_TYPE 19778
#define BF_REVERSED 0
#define B_OFF_BITS 54
#define BI_SIZE 40
#define BI_PLANES 1
#define BI_BIT_COUNT 24
#define BI_COMPRESSION 0
#define BI_X_PELS_PER_METER 0
#define BI_Y_PELS_PER_METER 0
#define BI_CLR_USED 0
#define BI_CLR_IMPORTANT 0
#pragma pack(push, 1)

#define PIXEL_SIZE 3
struct bmp_header
{
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};

struct bmp_header create_header(uint32_t width, uint32_t height);
enum read_status validate_header(const struct bmp_header header);
#pragma pack(pop)
#endif //LAB5_HEADER_H
