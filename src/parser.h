//
// Created by 1 on 2021/7/4.
//

#ifndef ACC_PARSER_H
#define ACC_PARSER_H

#include <vector>
#include <iostream>
#include "token.h"
#include "ast.h"
#include "type.h"
#include "diagnostic.h"

// @formatter:off
class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens) : tokens(tokens), index(0) {}

    TranslationUnit *parse();

protected:
    const std::vector<Token> &tokens;
    int index;

    Token consume(TokenType type);
    bool match(TokenType type);
    inline Token peek();
    inline Token next();

protected:
    void log_error(const char* fmt, ...);

protected:
    std::map<std::string, StructType*> structMap;
    std::map<std::string, FuncDef*> funcMap;

    Type *parseTypeSpecifier();
    void parseStructDef(StructType *baseType);
    FuncDef *parseFuncDef(Type *returnType, const Token& id);
    VarDef *parseVarDef(Type *baseType, const Token& id);

    Identifier *parseIdentifier();

    Expr* parseExpr();
    Expr* parsePrimaryExpr();
    Expr *parsePostfixExpr();
    Expr *parseUnaryExpr();
    Expr *parseCastExpr();
    Expr *parseAssignExpr();
    Expr *parseConditionalExpr();
    Expr *parseLogicalOrExpr();
    Expr *parseLogicalAndExpr();
    Expr *parseEqualityExpr();
    Expr *parseRelationalExpr();
    Expr *parseAdditiveExpr();
    Expr *parseMultiplicativeExpr();

    static UnaryOp convert2UnaryOp(TokenType type);
    static BinaryOp convert2BinaryOp(TokenType type);

    inline static bool isUnaryOperator(TokenType type);
    inline static bool isRelationalOp(TokenType type);
    inline static bool isEqualityOp(TokenType type);
    inline static bool isAdditiveOp(TokenType type);
    inline static bool isMultiplicativeOp(TokenType type);
    inline static bool isAssignOp(TokenType type);

    Stmt *parseIfStmt();
    CompoundStmt * parseCompoundStmt();
    Stmt *parseExprStmt();
    Stmt *parseReturnStmt();

};
// @formatter:on

#endif //ACC_PARSER_H
