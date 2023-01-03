//
// Created by Never on 12/29/2022.
//

#ifndef LAB5_FILE_H
#define LAB5_FILE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define ARGUMENT_ERROR "Number of arguments is not match\n"

#define READ_HEADER_ERROR "Cannot read header\n"
#define WRITE_HEADER_ERROR "Cannot write header\n"
#define READ_IMAGE_ERROR "Cannot read image\n"
#define WRITE_IMAGE_ERROR "Cannot write image\n"
#define ROTATE_IMAGE_ERROR "Cannot rotate image\n"
#define OPEN_FILE_ERROR "Cannot open file\n"
#define CLOSE_FILE_ERROR "Cannot close file \n"
#define SIGNATURE_ERROR "Signature is invalid"

#define WRITER_ERROR "Cannot write file\n"
#define ALL_OK "Все хорошо\n"

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
//void sepia_asm_inplace(struct image* img);

enum read_status  {
    READ_OK = 0,
    READ_ERROR = 1,
    READ_INVALID_SIGNATURE = 2,
    READ_INVALID_BITS = 3,
    READ_INVALID_HEADER = 4
    /* коды других ошибок  */
};

enum write_status  {
    WRITE_OK = 0,
    WRITE_ERROR = 1
    /* коды других ошибок  */
};

void print_err(char msg[]);
void print_read_status(int st);
void print_write_status(int st);
int check_arguments(int num_of_argument);

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

enum read_status from_bmp( FILE* in, struct image* img );
enum write_status to_bmp( FILE* out, struct image const* img );

#endif //LAB5_FILE_H
