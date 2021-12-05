//
// Created by 1 on 2021/12/4.
//

#include "semantic.h"
#include "error.h"

void SemanticAnalyzer::visit(TranslationUnit *node) {
    for(auto decl : node->defs) {
        decl->accept(this);
    }
}

void SemanticAnalyzer::visit(CompoundStmt *node) {
    enter_scope();
    for(auto stmt : node->items) {
        stmt->accept(this);
    }
    exit_scope();
}

void SemanticAnalyzer::visit(ExprStmt *node) {
    node->expr->accept(type_checker);
}

void SemanticAnalyzer::visit(IfStmt *node) {
    node->cond->accept(type_checker);
    
}

void SemanticAnalyzer::visit(ReturnStmt *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(VarDef *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(FuncDef *node) {
    Visitor::visit(node);
}

void TypeChecker::visit(Integer *node) {
    Visitor::visit(node);
}

void TypeChecker::visit(Identifier *node) {
    Visitor::visit(node);
}

void TypeChecker::visit(ArrayRef *node) {
    Visitor::visit(node);
}

void TypeChecker::visit(FunCall *node) {
    Visitor::visit(node);
}

void TypeChecker::visit(Unary *node) {
    Visitor::visit(node);
}

void TypeChecker::visit(Cast *node) {
    Visitor::visit(node);
}

void TypeChecker::visit(Binary *node) {
    Visitor::visit(node);
}

void TypeChecker::visit(Assignment *node) {
    Visitor::visit(node);
}
