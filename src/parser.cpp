#include "parser.h"
#include <iostream>

TranslationUnit Parser::parse() {
    return TranslationUnit();
}
Expr Parser::parseExpr() {
    return parseAssignmentExpr();
}
Expr Parser::parseAssignmentExpr() {
    Expr lvalue = parseUnaryExpr();
    consume(TokenType::ASSIGN);
    Expr rvalue = parseExpr();
    return Assignment(lvalue, rvalue)
}
Expr Parser::parseUnaryExpr() {
    return Expr();
}
void Parser::consume(TokenType type) {
    if(tokens[index].type == type) {
        index++;
    } else {
        std::cerr << "expect " << tokentype2string[type] << std::endl;
        exit(-1);
    }
}
