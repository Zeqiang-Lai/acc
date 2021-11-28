//
// Created by 1 on 2021/11/28.
//

#ifndef ACC_VISITOR_H
#define ACC_VISITOR_H

class Integer;
class Identifier;
class ArrayRef;
class FunCall;
class Unary;
class Cast;
class Binary;
class Assignment;

class Visitor {
public:
    //@formatter:off
    virtual void visit(Integer *node) {};
    virtual void visit(Identifier *node) {};
    virtual void visit(ArrayRef *node) {};
    virtual void visit(FunCall *node) {};
    virtual void visit(Unary *node) {};
    virtual void visit(Cast *node) {};
    virtual void visit(Binary *node) {};
    virtual void visit(Assignment *node) {};
    //@formatter:on
};


#endif //ACC_VISITOR_H