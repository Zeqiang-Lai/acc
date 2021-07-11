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
    Node(const Span &span) : span(span) {}

    Node() {}

    Span span;
};

class Stmt : public Node{

};


class Expr : public Node {

};

class Identifier : public Expr {
public:
    Identifier(const string &name) : name(name) {}

    string name;
};

class Integer : public Expr {
public:
    Integer(int number) : number(number) {}

    int number;
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

class Statement;

class CompoundStatement;

class ExprStatement;

class IfStatement;

class IterationStatement;

class JumpStatement;

class TranslationUnit;

class FunctionDefinition;

class TypeSpecifier : public Node{
public:
    string name;
    Type type;
};

class Declaration : public Node {

};


class FunctionDefinition : public Declaration{
public:
    TypeSpecifier *returnType;
    Identifier *name;
    vector<pair<TypeSpecifier *, Identifier *>> arguments;
    CompoundStatement *body;

    FunctionDefinition(TypeSpecifier *return_type,
                       Identifier *name,
                       const vector<pair<TypeSpecifier *, Identifier *>> &arguments,
                       CompoundStatement *body)
                       : returnType(return_type), name(name), arguments(arguments), body(body) {}
};

class VarDeclaration : public Declaration{
public:
    TypeSpecifier *type;
    Identifier *name;
    Expr *initializer;

    VarDeclaration(TypeSpecifier *type, Identifier *name, Expr *initializer)
            : type(type), name(name), initializer(initializer) {}
};

class TranslationUnit {
public:
    vector<Declaration *> declarations;

    explicit TranslationUnit(const vector<Declaration *> &declarations) : declarations(declarations) {}
};

#endif //ACC_AST_H
