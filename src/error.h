//
// Created by 1 on 2021/11/28.
//

#ifndef ACC_ERROR_H
#define ACC_ERROR_H

#include <string>
#include <cstdarg>

void internal_error(const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);
    printf("\n");
    exit(-1);
}


#endif //ACC_ERROR_H
