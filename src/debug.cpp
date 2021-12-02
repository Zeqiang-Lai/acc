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

void ASTPrinter::visit(CompoundStmt *node) {
    print("CompoundStmt");
    indent();
    for(auto stmt : node->items) {
        stmt->accept(this);
    }
    deindent();
}

void ASTPrinter::visit(ExprStmt *node) {
    print("ExprStmt");
    indent();
    node->expr->accept(this);
    deindent();
}

void ASTPrinter::visit(IfStmt *node) {
    print("IfStmt");
    indent();

    print("Cond");
    indent();
    node->cond->accept(this);
    deindent();

    print("thenBody");
    indent();
    node->thenbody->accept(this);
    deindent();

    if(node->elsebody != nullptr) {
        print("elseBody");
        indent();
        node->elsebody->accept(this);
        deindent();
    }

    deindent();
}

void ASTPrinter::visit(Decl *node) {
    print("Decl");
    indent();

    print("Name(%s)", node->id->name.c_str());

    if(node->initializer != nullptr) {
        print("Init");
        indent();
        node->initializer->accept(this);
        deindent();
    }

    deindent();
}

void ASTPrinter::visit(FuncDef *node) {
    print("FuncDef");
    indent();

    print("Name(%s)", node->id->name.c_str());

    print("Params");
    indent();
    for(auto param : node->params) {
        print("Param(%s)", param->name.c_str());
    }
    deindent();

    print("Body");
    indent();
    node->body->accept(this);
    deindent();

    deindent();
}
