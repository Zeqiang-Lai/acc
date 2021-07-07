//
// Created by 1 on 2021/7/4.
//

#ifndef ACC_PARSER_H
#define ACC_PARSER_H

#include <vector>
#include "token.h"
#include "ast.h"

class Parser {
public:
    explicit Parser(const vector<Token>& tokens) : tokens(tokens), index(0) {}
    TranslationUnit parse();

protected:
    Expr parseExpr();
    Expr parseAssignmentExpr();
    Expr parseConditionalExpr();
    Expr parseLogicalOrExpr();
    Expr parseLogicalAndExpr();
    Expr parseInclusiveOrExpr();
    Expr parseExclusiveOrExpr();
    Expr parseAndExpr();
    Expr parseEqualityExpr();
    Expr parseRelationalExpr();
    Expr parseShiftExpr();
    Expr parseAdditiveExpr();
    Expr parseMultiplicativeExpr();
    Expr parseCastExpr();
    Expr parseUnaryExpr();
    Expr parsePostfixExpr();
    Expr parsePrimaryExpr();

    void consume(TokenType type);

    const vector<Token>& tokens;
    int index;
};


#endif //ACC_PARSER_H
