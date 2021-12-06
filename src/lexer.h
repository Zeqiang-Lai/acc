#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>

#include "token.h"

using namespace std;

//@formatter:off
class Lexer {
public:
    explicit Lexer(const string& code) : code(code), idx(0), row(1), col(1) {}
    Token lex();

private:
    const string& code;
    int idx;
    int row, col, pre_col;

    char peek();
    char next();
    char previous();
    void back();
    bool match(char target);
    void expect(char target);

private:
    int mark_row, mark_col;
    void mark_begin();

private:
    void skip_whitespace();
    void skip_comment();

    Token character();
    Token identifier();
    Token number();

    Token make_token(TokenType type);
    Token make_token(Token base);

};
//@formatter:on

#endif