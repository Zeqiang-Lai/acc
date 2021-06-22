#include <iostream>
using namespace std;


enum class TokenType : unsigned {
    ID,
    LITERAL,
    INT_CONST, FLOAT_CONST, CHAR_CONST,
    

    // symbols
    EQ, LEQ, GEQ, GT, LT, NEQ,
    ASSIGN,
    ADD, MINUS, DIV, MULT, MOD,
    REL_AND, REL_OR, REL_NOT,
    AND, OR, NOT, XOR,
    COMMA, COLON, SEMICOLON,
    LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE,

    // keywords
    INT, FLOAT, DOUBLE, CHAR, VOID,
    IF, ELSE, FOR, WHILE, RETURN, BREAK, CONTINUE,

    INVALID, END, 
};

int main() {

    TokenType type = TokenType::DOUBLE;
    if(type >= TokenType::INT && type <= TokenType::CONTINUE)
        cout << "keyword" << endl;

    return 0;
}