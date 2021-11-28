//
// Created by 1 on 2021/11/28.
//

#ifndef ACC_DEBUG_H
#define ACC_DEBUG_H

#include "ast.h"
#include "visitor.h"

class ASTPrinter : public Visitor{
public:
    //@formatter:off
    void visit(Integer *node) override;
    void visit(Identifier *node) override;
    void visit(ArrayRef *node) override;
    void visit(FunCall *node) override;
    void visit(Unary *node) override;
    void visit(Cast *node) override;
    void visit(Binary *node) override;
    void visit(Assignment *node) override;

protected:
    int indent_level;
    void indent() { indent_level += 1; }
    void deindent() { indent_level = max(0, indent_level-1);}
    //@formatter:on
};


#endif //ACC_DEBUG_H
