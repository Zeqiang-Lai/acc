#ifndef TOKEN_H
#define TOKEN_H

#include <map>
#include <string>
using namespace std;

enum class TokenType : unsigned {
    ID,
    LITERAL,
    INT_CONST, FLOAT_CONST, CHAR_CONST,
    

    // symbols
    EQ, LEQ, GEQ, GT, LT, NEQ,
    ASSIGN, ADD_ASSIGN, MINUS_ASSIGN, DIV_ASSIGN, MULT_ASSIGN, MOD_ASSIGN,
    ADD, MINUS, DIV, MULT, MOD,
    INCREMENT,DECREMENT,
    LOGIC_AND, LOGIC_OR, LOGIC_NOT,
    AND, OR, NOT, XOR,
    COMMA, COLON, SEMICOLON, COND,
    LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE,

    // keywords
    INT, FLOAT, DOUBLE, CHAR, VOID,
    IF, ELSE, FOR, WHILE, RETURN, BREAK, CONTINUE,

    NEWLINE, 
    INVALID, END

};

static map<TokenType, string> tokentype2string = {
    {TokenType::ID, "ID"}
};

static map<string, TokenType> keywordmap = {
    {"int", TokenType::INT},
    {"float", TokenType::FLOAT},
    {"double", TokenType::DOUBLE},
    {"char", TokenType::CHAR},
    {"void", TokenType::VOID},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"for", TokenType::FOR},
    {"while", TokenType::WHILE},
    {"return", TokenType::RETURN},
    {"break", TokenType::BREAK},
    {"continue", TokenType::CONTINUE},
};

class Token {
public:
    TokenType type;

    int int_value;
    double float_value;
    char char_value;
    string string_value;

    Token(TokenType type) : type(type) {}
    Token(TokenType type, double float_value) : type(type), float_value(float_value) {}
    Token(TokenType type, int int_value) : type(type), int_value(int_value) {}
    Token(TokenType type, char char_value) : type(type), char_value(char_value) {}
    Token(TokenType type, string string_value) : type(type), string_value(string_value) {}

    string to_string() {
        return tokentype2string[type];
    }
};

#endif