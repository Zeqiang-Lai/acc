//
// Created by 1 on 2021/7/4.
//

#ifndef ACC_PARSER_H
#define ACC_PARSER_H

#include <vector>
#include "token.h"
#include "ast.h"

// @formatter:off
class Parser {
public:
    explicit Parser(const vector<Token> &tokens) : tokens(tokens), index(0) {}

    TranslationUnit *parse();

protected:
    Type *parseTypeSpecifier();
    Type *parseStruct();
    Type *parseStructDeclarationList(Token* id);

protected:
    Token consume(TokenType type);
    bool match(TokenType type);
    inline Token peek();
    inline Token next();

protected:
    const vector<Token> &tokens;
    int index;

    Node *parseFuncOrVariable();

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

    Stmt *parseStmt();
    Stmt *parseIfStmt();
    CompoundStmt * parseCompoundStmt();
    Stmt *parseExprStmt();
};
// @formatter:on

#endif //ACC_PARSER_H
