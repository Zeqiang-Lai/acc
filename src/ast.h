//
// Created by 1 on 2021/7/4.
//

#ifndef ACC_AST_H
#define ACC_AST_H

#include <vector>
#include <string>
#include "span.h"
#include "type.h"
#include "visitor.h"

class Node {
public:
    Span span;
public:
    Node(const Span &span) : span(span) {}

    Node() {}

    virtual void accept(Visitor *visitor) = 0;

};

// region Expression:

class Expr : public Node {
public:
    Type *evalType;
public:
    void accept(Visitor *visitor) override = 0;
};

class Identifier : public Expr {
public:
    std::string name;
    Node *def;
public:
    Identifier(const std::string &name) : name(name), def(nullptr) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }
};

class Integer : public Expr {
public:
    int number;
public:
    Integer(int number) : number(number) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }

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

    void accept(Visitor *visitor) override { visitor->visit(this); }

};

class FunCall : public Expr {
public:
    Expr *func;
    std::vector<Expr *> args;

    FunCall(Expr *func, const std::vector<Expr *> &args) : func(func), args(args) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }

};

enum class UnaryOp {
    Complement, // ^
    Not,     // !
    Pointer,    // *
    Address,     // &
    Positive, Negative  // + -
};

class Unary : public Expr {
public:
    Expr *operand;
    UnaryOp op;

    Unary(Expr *operand, UnaryOp op) : operand(operand), op(op) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }

};

class Cast : public Expr {
public:
    Expr *op;

};

enum class BinaryOp {
    Plus, Minus,
    Multiply, Divide, Modulo,
    Less, Greater,
    LessOrEqual, GreaterOrEqual,
    Equals, NotEquals,
    LogicalAnd, LogicalOr
};

class Binary : public Expr {
public:
    Expr *lhs, *rhs;
    BinaryOp op;

    Binary(Expr *lhs, Expr *rhs, BinaryOp op) : lhs(lhs), rhs(rhs), op(op) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }

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

    void accept(Visitor *visitor) override { visitor->visit(this); }

};


// endregion

// region Statement

class Stmt : public Node {
public:
    void accept(Visitor *visitor) override {}
};

class CompoundStmt : public Stmt {
public:
    std::vector<Node *> items;

    CompoundStmt(const std::vector<Node *> &items) : items(items) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }
};

class ExprStmt : public Stmt {
public:
    Expr *expr;

    ExprStmt(Expr *expr) : expr(expr) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }

};

class IfStmt : public Stmt {
public:
    Expr *cond;
    CompoundStmt *thenbody;
    CompoundStmt *elsebody;

    IfStmt(Expr *cond, CompoundStmt *thenbody, CompoundStmt *elsebody) : cond(cond), thenbody(thenbody),
                                                                         elsebody(elsebody) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }
};

class IterationStmt {

};

class JumpStmt;

class ReturnStmt : public Stmt {
public:
    Expr *value;

    ReturnStmt(Expr *value) : value(value) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }
};

// endregion

class VarDef : public Node {
public:
    std::string name;
    Expr *initializer;
    Type *type;
public:
    VarDef(const std::string &name, Expr *initializer, Type *type) : name(name), initializer(initializer), type(type) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }
};

class FuncDef : public Node {
public:
    std::string name;
    CompoundStmt *body;
    Type *returnType;
    std::map<std::string, Type *> paramTypes;
public:
    FuncDef(const std::string &name, CompoundStmt *body, Type *returnType,
            const std::map<std::string, Type *> &paramTypes) : name(name), body(body), returnType(returnType),
                                                               paramTypes(paramTypes) {}

    void accept(Visitor *visitor) override { visitor->visit(this); }
};

class TranslationUnit {
public:
    std::vector<Node *> defs;
public:
    explicit TranslationUnit(const std::vector<Node *> &defs) : defs(defs) {}
};

#endif //ACC_AST_H
