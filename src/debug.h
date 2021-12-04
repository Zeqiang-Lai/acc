//
// Created by 1 on 2021/11/28.
//

#ifndef ACC_DEBUG_H
#define ACC_DEBUG_H

#include <cstdarg>
#include <map>
#include "ast.h"
#include "visitor.h"


class ASTPrinter : public Visitor {
public:
    //@formatter:off
    void print(Node* node) { node->accept(this); }

    void visit(TranslationUnit *node) override;
    void visit(Integer *node) override;
    void visit(Identifier *node) override;
    void visit(ArrayRef *node) override;
    void visit(FunCall *node) override;
    void visit(Unary *node) override;
    void visit(Cast *node) override;
    void visit(Binary *node) override;
    void visit(Assignment *node) override;

    void visit(CompoundStmt *node) override;
    void visit(ExprStmt *node) override;
    void visit(IfStmt *node) override;
    void visit(ReturnStmt *node) override;

    void visit(Decl *node) override;
    void visit(FuncDef *node) override;

protected:
    int indent_level = 0;
    void indent() { indent_level += 1; }
    void deindent() { indent_level = max(0, indent_level-1);}
    void print(const char* fmt, ...) const {
        for(int i=0; i<indent_level; i++) printf(" ");
        va_list arg;
        va_start(arg, fmt);
        vprintf(fmt, arg);
        va_end(arg);
        printf("\n");
    }

    //@formatter:on
};

static std::map<BinaryOp, string> binaryOp2string = {
        {BinaryOp::Plus,           "+"},
        {BinaryOp::Minus,          "-"},
        {BinaryOp::Multiply,       "*"},
        {BinaryOp::Divide,         "/"},
        {BinaryOp::Modulo,         "%"},
        {BinaryOp::Less,           "<"},
        {BinaryOp::Greater,        ">"},
        {BinaryOp::LessOrEqual,    "<="},
        {BinaryOp::GreaterOrEqual, ">="},
        {BinaryOp::Equals,         "=="},
        {BinaryOp::NotEquals,      "!="},
        {BinaryOp::LogicalAnd,     "&&"},
        {BinaryOp::LogicalOr,      "||"},
};

static std::map<UnaryOp, string> unaryOp2string = {
        {UnaryOp::Complement, "^"},
        {UnaryOp::Not,        "!"},
        {UnaryOp::Pointer,    "*"},
        {UnaryOp::Address,    "&"},
        {UnaryOp::Positive,   "+"},
        {UnaryOp::Negative,   "-"},
};

#endif //ACC_DEBUG_H
