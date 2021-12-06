#include <iostream>
#include "token.h"

std::ostream &operator<<(std::ostream &out, const Token &token) {
    out << "Token";
    out << "[" << token.row << ":" << token.col << ":" << token.length <<  "]";
    out << "(" << tokentype2string[token.type];
    if (token.type == TokenType::ID) out << "," << token.string_value << ")";
    else if (token.type == TokenType::INT_CONST) out << "," << token.int_value << ")";
    else if (token.type == TokenType::FLOAT_CONST) out << "," << token.float_value << ")";
    else if (token.type == TokenType::CHAR_CONST) out << "," << token.char_value << ")";
    else out << ")";
    return out;
}
