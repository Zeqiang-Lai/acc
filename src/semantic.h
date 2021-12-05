//
// Created by 1 on 2021/12/4.
//

#ifndef ACC_SEMANTIC_H
#define ACC_SEMANTIC_H

#include "visitor.h"
#include "ast.h"
#include "scope.h"

/**
 * Type checking
 *  - assignment type must match
 *  - condition must be int
 * Name resolve:
 *  - bind id use to its def (var, func call)
 * Control structure:
 *  - break, continue must be in loop
 *  - non-void function must have return
 */

class TypeChecker : public Visitor {
public:
    //@formatter:off
    void visit(Integer *node) override;
    void visit(Identifier *node) override;
    void visit(ArrayRef *node) override;
    void visit(FunCall *node) override;
    void visit(Unary *node) override;
    void visit(Cast *node) override;
    void visit(Binary *node) override;
    void visit(Assignment *node) override;
    //@formatter:on
};

class SemanticAnalyzer : public Visitor {
public:
    //@formatter:off
    void visit(TranslationUnit *node) override;
    void visit(CompoundStmt *node) override;
    void visit(ExprStmt *node) override;
    void visit(IfStmt *node) override;
    void visit(ReturnStmt *node) override;
    void visit(VarDef *node) override;
    void visit(FuncDef *node) override;
    //@formatter:on
public:
    SemanticAnalyzer() {
        cur_scope = new Scope(nullptr);
        type_checker = new TypeChecker();
    }

    ~SemanticAnalyzer() {
        delete cur_scope;
        delete type_checker;
    }

protected:
    void enter_scope() {
        auto scope = new Scope(cur_scope);
        cur_scope = scope;
    }

    void exit_scope() {
        auto scope = cur_scope->enclosing;
        delete cur_scope;
        cur_scope = scope;
    }

protected:
    Scope *cur_scope;
    Visitor *type_checker;
};


#endif //ACC_SEMANTIC_H
