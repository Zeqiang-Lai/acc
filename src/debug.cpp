//
// Created by 1 on 2021/11/28.
//

#include "debug.h"

void ASTPrinter::visit(Integer *node) {
    print("Integer(%d)", node->number);
}

void ASTPrinter::visit(Identifier *node) {
    print("ID(%s)", node->name.c_str());
}

void ASTPrinter::visit(ArrayRef *node) {
    print("ArrayRef");
    indent();

    print("Array");
    indent();
    node->array->accept(this);
    deindent();

    print("index");
    indent();
    node->index->accept(this);
    deindent();

    deindent();
}

void ASTPrinter::visit(FunCall *node) {
    print("FunCall");
    indent();

    print("Callee");
    indent();
    node->func->accept(this);
    deindent();

    print("Args");
    indent();
    for (auto arg: node->args) {
        arg->accept(this);
    }
    deindent();

    deindent();
}

void ASTPrinter::visit(Unary *node) {
    print("Unary(%s)", unaryOp2string[node->op].c_str());
    indent();
    node->operand->accept(this);
    deindent();
}

void ASTPrinter::visit(Cast *node) {
    print("Cast");
}

void ASTPrinter::visit(Binary *node) {
    print("Binary(%s)", binaryOp2string[node->op].c_str());
    indent();
    node->lhs->accept(this);
    node->rhs->accept(this);
    deindent();
}

void ASTPrinter::visit(Assignment *node) {
    print("Assignment");
    indent();
    node->lvalue->accept(this);
    node->rvalue->accept(this);
    deindent();
}
