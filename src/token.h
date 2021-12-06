#ifndef TOKEN_H
#define TOKEN_H

#include <map>
#include <string>

enum class TokenType : unsigned {
    ID,
    LITERAL,
    INT_CONST, FLOAT_CONST, CHAR_CONST,


    // symbols
    EQ, LEQ, GEQ, GT, LT, NEQ,
    ASSIGN, ADD_ASSIGN, MINUS_ASSIGN, DIV_ASSIGN, MULTI_ASSIGN, MOD_ASSIGN,
    ADD, MINUS, DIV, MULTI, MOD,
    INCREMENT, DECREMENT,
    LOGIC_AND, LOGIC_OR, LOGIC_NOT,
    AND, OR, NOT, XOR,
    COMMA, COLON, SEMICOLON, COND,
    LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE,

    // keywords
    INT, FLOAT, DOUBLE, CHAR, VOID,
    IF, ELSE, FOR, WHILE, RETURN, BREAK, CONTINUE, STRUCT,

    NEWLINE,
    INVALID, END

};

//@formatter:off
class Token {
public:
    TokenType type;

    int int_value;
    double float_value;
    char char_value;
    std::string string_value;

    int row, col, length;

    Token(TokenType type) : type(type) {}
    Token(TokenType type, double float_value) : type(type), float_value(float_value) {}
    Token(TokenType type, int int_value) : type(type), int_value(int_value) {}
    Token(TokenType type, char char_value) : type(type), char_value(char_value) {}
    Token(TokenType type, std::string string_value) : type(type), string_value(string_value) {}

    void setspan(int row, int col, int length) {
        this->row = row;
        this->col = col;
        this->length = length;
    }

    friend std::ostream &operator<<(std::ostream &out, const Token &token);
};
//@formatter:on

static std::map<std::string, TokenType> keywordmap = {
        {"int",      TokenType::INT},
        {"float",    TokenType::FLOAT},
        {"double",   TokenType::DOUBLE},
        {"char",     TokenType::CHAR},
        {"void",     TokenType::VOID},
        {"if",       TokenType::IF},
        {"else",     TokenType::ELSE},
        {"for",      TokenType::FOR},
        {"while",    TokenType::WHILE},
        {"return",   TokenType::RETURN},
        {"break",    TokenType::BREAK},
        {"continue", TokenType::CONTINUE},
        {"struct",   TokenType::STRUCT},
};

static std::map<TokenType, std::string> tokentype2string = {
        {TokenType::ID,           "ID"},
        {TokenType::LITERAL,      "LITERAL"},
        {TokenType::INT_CONST,    "INT_CONST"},
        {TokenType::FLOAT_CONST,  "FLOAT_CONST"},
        {TokenType::CHAR_CONST,   "CHAR_CONST"},
        {TokenType::EQ,           "EQ"},
        {TokenType::LEQ,          "LEQ"},
        {TokenType::GEQ,          "GEQ"},
        {TokenType::GT,           "GT"},
        {TokenType::LT,           "LT"},
        {TokenType::NEQ,          "NEQ"},
        {TokenType::ASSIGN,       "ASSIGN"},
        {TokenType::ADD_ASSIGN,   "ADD_ASSIGN"},
        {TokenType::MINUS_ASSIGN, "MINUS_ASSIGN"},
        {TokenType::DIV_ASSIGN,   "DIV_ASSIGN"},
        {TokenType::MULTI_ASSIGN, "MULTI_ASSIGN"},
        {TokenType::MOD_ASSIGN,   "MOD_ASSIGN"},
        {TokenType::ADD,          "ADD"},
        {TokenType::MINUS,        "MINUS"},
        {TokenType::DIV,          "DIV"},
        {TokenType::MULTI,        "MULTI"},
        {TokenType::MOD,          "MOD"},
        {TokenType::INCREMENT,    "INCREMENT"},
        {TokenType::DECREMENT,    "DECREMENT"},
        {TokenType::LOGIC_AND,    "LOGIC_AND"},
        {TokenType::LOGIC_OR,     "LOGIC_OR"},
        {TokenType::LOGIC_NOT,    "LOGIC_NOT"},
        {TokenType::AND,          "AND"},
        {TokenType::OR,           "OR"},
        {TokenType::NOT,          "NOT"},
        {TokenType::XOR,          "XOR"},
        {TokenType::COMMA,        "COMMA"},
        {TokenType::COLON,        "COLON"},
        {TokenType::SEMICOLON,    "SEMICOLON"},
        {TokenType::COND,         "COND"},
        {TokenType::LPAREN,       "LPAREN"},
        {TokenType::RPAREN,       "RPAREN"},
        {TokenType::LBRACKET,     "LBRACKET"},
        {TokenType::RBRACKET,     "RBRACKET"},
        {TokenType::LBRACE,       "LBRACE"},
        {TokenType::RBRACE,       "RBRACE"},
        {TokenType::INT,          "INT"},
        {TokenType::FLOAT,        "FLOAT"},
        {TokenType::DOUBLE,       "DOUBLE"},
        {TokenType::CHAR,         "CHAR"},
        {TokenType::VOID,         "VOID"},
        {TokenType::IF,           "IF"},
        {TokenType::ELSE,         "ELSE"},
        {TokenType::FOR,          "FOR"},
        {TokenType::WHILE,        "WHILE"},
        {TokenType::RETURN,       "RETURN"},
        {TokenType::BREAK,        "BREAK"},
        {TokenType::CONTINUE,     "CONTINUE"},
        {TokenType::STRUCT,       "STRUCT"},
        {TokenType::INVALID,      "INVALID"},
        {TokenType::END,          "END"},
};

#endif