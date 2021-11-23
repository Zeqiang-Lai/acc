//
// Created by laizeqiang on 2021/7/12.
//

#ifndef ACC_SCOPE_H
#define ACC_SCOPE_H

#include <map>
#include "type.h"

class Scope {
protected:
    Scope* enclosing;
    std::map<std::string, Type*> symbols;
public:
    Scope(Scope *enclosing) : enclosing(enclosing) {}

};


#endif //ACC_SCOPE_H
