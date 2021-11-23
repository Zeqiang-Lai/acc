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
    explicit Parser(const vector<Token> &tokens) : tokens(tokens), index(0) {}

    TranslationUnit *parse();

protected:
    Type *parseTypeSpecifier();
    Type *parseStruct();
    Type *parseStructDeclarationList(Token* id);

protected:
    void consume(TokenType type);
    bool match(TokenType type);
    Token peek();
    Token next();

protected:
    const vector<Token> &tokens;
    int index;
};


#endif //ACC_PARSER_H
