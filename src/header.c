//
// Created by Never on 12/29/2022.
//
#include "../header/header.h"
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