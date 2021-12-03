//
// Created by 1 on 2021/12/3.
//

#include "codegen.h"

void LLVMEmitter::visit(Integer *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(Identifier *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(ArrayRef *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(FunCall *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(Unary *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(Cast *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(Binary *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(Assignment *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(CompoundStmt *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(ExprStmt *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(IfStmt *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(ReturnStmt *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(Decl *node) {
    Visitor::visit(node);
}

void LLVMEmitter::visit(FuncDef *node) {
    Visitor::visit(node);
}
