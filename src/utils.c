//
// Created by Never on 12/29/2022.
//
#include "../header/utils.h"
#include "../header/errors_list.h"
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