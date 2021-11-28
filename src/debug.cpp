//
// Created by 1 on 2021/11/28.
//

#include "debug.h"

void ASTPrinter::visit(Integer *node) {
    Visitor::visit(node);
}

void ASTPrinter::visit(Identifier *node) {
    Visitor::visit(node);
}

void ASTPrinter::visit(ArrayRef *node) {
    Visitor::visit(node);
}

void ASTPrinter::visit(FunCall *node) {
    Visitor::visit(node);
}

void ASTPrinter::visit(Unary *node) {
    Visitor::visit(node);
}

void ASTPrinter::visit(Cast *node) {
    Visitor::visit(node);
}

void ASTPrinter::visit(Binary *node) {
    Visitor::visit(node);
}

void ASTPrinter::visit(Assignment *node) {
    Visitor::visit(node);
}
