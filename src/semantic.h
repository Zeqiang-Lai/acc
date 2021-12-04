//
// Created by 1 on 2021/12/4.
//

#ifndef ACC_SEMANTIC_H
#define ACC_SEMANTIC_H

#include "visitor.h"

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
class SemanticAnalyzer : public Visitor {
public:
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
};


#endif //ACC_SEMANTIC_H
