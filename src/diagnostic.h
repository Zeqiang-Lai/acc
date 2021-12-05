//
// Created by 1 on 2021/11/28.
//

#ifndef ACC_DIAGNOSTIC_H
#define ACC_DIAGNOSTIC_H

#include <string>
#include <cstdarg>

void internal_error(const char* fmt, ...) {
    printf("error: ");
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);
    printf("\n");
    exit(-1);
}

void warning(const char* fmt, ...) {
    printf("warning: ");
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);
    printf("\n");
}

#endif //ACC_DIAGNOSTIC_H
