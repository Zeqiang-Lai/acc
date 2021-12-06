//
// Created by laizeqiang on 2021/12/6.
//

#include <string>
#include <cstdarg>

void internal_error(const char *fmt, ...) {
    printf("internal error: ");
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);
    printf("\n");
    exit(-1);
}

void error(const char *fmt, ...) {
    printf("error: ");
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);
    printf("\n");
    exit(-1);
}

void warning(const char *fmt, ...) {
    printf("warning: ");
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);
    printf("\n");
}