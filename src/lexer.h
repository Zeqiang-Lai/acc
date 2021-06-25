#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>

#include "token.h"

using namespace std;

class Lexer {
public:
    Lexer(string code) : code(code), idx(0) {}
    Token lex();

private:
    string code;
    int idx;

    char peek();
    char next();
    char previous();
    void back();
    bool match(char target);

    void skip_whitespace();
    void skip_comment();
    Token identifier();
    Token number();

    Token make_token(TokenType type);
};

#endif