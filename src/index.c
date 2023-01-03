//
// Created by Never on 12/29/2022.
//

#include "../header/file.h"
#include "../header/errors_list.h"

int main() {

    FILE* file = fopen("input1.bmp", "rb+");

    if(!file) {
//        fprintf(stderr, OPEN_FILE_ERROR);
        fprintf(stderr, "cannot open input file!");
        return 0;
    }

    FILE* new_file = fopen("output.bmp", "wb+");

    if(!new_file) {
        if(!fclose(file)) {
            fprintf(stderr, CLOSE_FILE_ERROR);
            return 0;
        }
        fprintf(stderr, OPEN_FILE_ERROR);
        return 0;
    }

    struct image image = {0};

    print_read_status(from_bmp(file, &image));
//    if(!check_image(image) ) {
//        fprintf(stderr, ROTATE_IMAGE_ERROR);
//        return 0;
//    }

//    struct image new_image = sepia_c_inplace(&image);
    sepia_c_inplace(&image);
//    if(!check_image(new_image) ) {
//        fprintf(stderr, ROTATE_IMAGE_ERROR);
//        return 0;
//    }

//    print_write_status(to_bmp(new_file, &new_image));

    print_write_status(to_bmp(new_file, &image));
    free_img(&image);

//    free_img(&new_image);




    if(fclose(file) != 0 || fclose(new_file) != 0) {
        fprintf(stderr, CLOSE_FILE_ERROR);
        return 0;
    }

    return 0;
}
