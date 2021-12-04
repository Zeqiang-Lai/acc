//
// Created by 1 on 2021/12/4.
//

#include "semantic.h"

void SemanticAnalyzer::visit(TranslationUnit *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(Integer *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(Identifier *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(ArrayRef *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(FunCall *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(Unary *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(Cast *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(Binary *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(Assignment *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(CompoundStmt *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(ExprStmt *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(IfStmt *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(ReturnStmt *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(Decl *node) {
    Visitor::visit(node);
}

void SemanticAnalyzer::visit(FuncDef *node) {
    Visitor::visit(node);
}
