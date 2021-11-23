//
// Created by 1 on 2021/7/4.
//

#ifndef ACC_AST_H
#define ACC_AST_H

#include <vector>
#include <string>
#include "span.h"
#include "type.h"

using namespace std;

class Node {
public:
    Span span;
public:
    Node(const Span &span) : span(span) {}
    Node() {}
};

// region Expression:

class Expr : public Node {

};

class Identifier : public Expr {
public:
    string name;
    Type* type;
public:
    Identifier(const string &name) : name(name) {}
};

class Integer : public Expr {
public:
    int number;
public:
    Integer(int number) : number(number) {}
};

class Float : public Expr {
public:
    Float(double number) : number(number) {}

    double number;
};

class Char : public Expr {
public:
    Char(char ch) : ch(ch) {}

    char ch;
};

class ArrayRef : public Expr {
public:
    Expr *array, *index;

    ArrayRef(Expr *array, Expr *index) : array(array), index(index) {}
};

class FunCall : public Expr {
public:
    Expr *func;
    vector<Expr *> parameters;

    FunCall(Expr *func, const vector<Expr *> &parameters) : func(func), parameters(parameters) {}
};

enum class OperatorTag {
    Complement, // ^
    Negate,     // !
    Pointer,    // *
    Address,     // &

    Plus, Minus,
    Multiply, Divide, Modulo,
    Less, Greater,
    LessOrEqual, GreaterOrEqual,
    Equals, NotEquals,
    LogicalAnd, LogicalOr
};

class Operator : public Node {
public:
    const OperatorTag tag;

    Operator(const OperatorTag tag) : tag(tag) {}
};

class Unary : public Expr {
public:
    Expr *operand;
    Operator *op;
};

class Cast : public Expr {
public:
    Expr *op;

};

class Binary : public Expr {
public:
    Expr *lhs, *rhs;
    Operator op;

    Binary(Expr *lhs, Expr *rhs, Operator op) : lhs(lhs), rhs(rhs), op(op) {}
};

class Conditional : public Expr {
public:
    Expr *cond, *thenExpr, *elseExpr;

    Conditional(Expr *cond, Expr *thenExpr, Expr *elseExpr) : cond(cond), thenExpr(thenExpr), elseExpr(elseExpr) {}
};

class Assignment : public Expr {
public:
    Expr *lvalue, *rvalue;

    Assignment(Expr *lvalue, Expr *rvalue) : lvalue(lvalue), rvalue(rvalue) {}
};


// endregion

// region Statement

class Stmt : public Node{

};

class CompoundStmt;

class ExprStmt;

class IfStmt;

class IterationStmt;

class JumpStmt;

// endregion

class Decl : public Node {
public:
    Identifier* id;
    Expr* initializer;
public:
    Decl(Identifier *id, Expr *initializer) : id(id), initializer(initializer) {}
};


class FuncDef : public Node{
public:
    Identifier *id;
    CompoundStmt *body;
public:
    FuncDef(Identifier *id, CompoundStmt *body) : id(id), body(body) {}
};

class TranslationUnit {
public:
    vector<Node *> declarations;
public:
    explicit TranslationUnit(const vector<Node *> &declarations) : declarations(declarations) {}
};

#endif //ACC_AST_H
