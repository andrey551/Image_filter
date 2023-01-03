//
// Created by Never on 12/29/2022.
//

#ifndef LAB5_FILE_H
#define LAB5_FILE_H

#include "header.h"
#include "image.h"
#include "utils.h"
#include <stdlib.h>

enum read_status from_bmp( FILE* in, struct image* img );
enum write_status to_bmp( FILE* out, struct image const* img );

#endif //LAB5_FILE_H
