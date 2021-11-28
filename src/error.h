//
// Created by 1 on 2021/11/28.
//

#ifndef ACC_ERROR_H
#define ACC_ERROR_H

#include <string>

void internal_error(const std::string& msg) {
    printf("%s", msg.c_str());
    exit(-1);
}

#endif //ACC_ERROR_H
