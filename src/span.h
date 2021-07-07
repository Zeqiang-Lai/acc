//
// Created by laizeqiang on 2021/7/5.
//

#ifndef ACC_SPAN_H
#define ACC_SPAN_H


class Span {
public:
    const int start, end;
    Span() : start(0), end(0) {}
    Span(int start, int end) : start(start), end(end) {}
    Span operator+(Span another) const;
};


#endif //ACC_SPAN_H
