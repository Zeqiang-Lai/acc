//
// Created by 1 on 2021/11/28.
//

#ifndef ACC_DIAGNOSTIC_H
#define ACC_DIAGNOSTIC_H

void internal_error(const char *fmt, ...);

void error(const char *fmt, ...);
void warning(const char *fmt, ...);

#endif //ACC_DIAGNOSTIC_H
