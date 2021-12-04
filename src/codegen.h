//
// Created by 1 on 2021/12/3.
//

#ifndef ACC_CODEGEN_H
#define ACC_CODEGEN_H

#include "visitor.h"
#include "ast.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"

//@formatter:off232
class LLVMEmitter : public Visitor{
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
//@formatter:on

protected:
    llvm::Value *tmp = nullptr;

    llvm::Value *emit(Node *node) {
        node->accept(this);
        return tmp;
    }

protected:
    std::unique_ptr<llvm::LLVMContext> context;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::Module> module;

public:
    explicit LLVMEmitter(const string &module_name) {
        // Open a new context and module.
        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>(module_name, *context);

        // Create a new builder for the module.
        builder = std::make_unique<llvm::IRBuilder<>>(*context);
    }
};

#endif //ACC_CODEGEN_H
