//
// Created by laizeqiang on 2021/7/5.
//

#include "span.h"

Span Span::operator+(Span another) const {
    return {this->start, another.end};
}