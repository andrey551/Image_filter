//
// Created by Never on 12/29/2022.
//

#ifndef LAB5_STAT_H
#define LAB5_STAT_H

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
#endif //LAB5_STAT_H
