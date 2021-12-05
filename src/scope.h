//
// Created by laizeqiang on 2021/7/12.
//

#ifndef ACC_SCOPE_H
#define ACC_SCOPE_H

#include <map>
#include "type.h"
#include "ast.h"

/**
 * Scope is used for name resolving,
 * in this phase, we need to bind any id ref to its def, including
 *  1. variable ref: in expr
 *  2. function ref: in FuncCall
 *  3. type ref: struct, not implemented yet
 */

class Scope {
public:
    Scope *enclosing;
    std::map<std::string, Node *> symbols;
public:
    explicit Scope(Scope *enclosing) : enclosing(enclosing) {}

    void define(const std::string &name, Node *symbol);
    Node *resolve(const std::string &name);
    Node *resolveLocally(const std::string &name);
};


#endif //ACC_SCOPE_H
