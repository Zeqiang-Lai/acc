#include "parser.h"
#include <iostream>

TranslationUnit *Parser::parse() {
    vector<Declaration *> declarations;
    while (!match(TokenType::END)) {
        declarations.push_back(parseDeclaration());
    }
    return new TranslationUnit(declarations);
}

Declaration *Parser::parseDeclaration() {
    auto type = parseTypeSpecifier();
    auto id = parseIdentifier();

    // it is a function definition
    if(match(TokenType::LPAREN)) {
        vector<pair<TypeSpecifier*, Identifier*>> arguments;
        if(!match(TokenType::RPAREN)) {
            do {
                auto paramType = parseTypeSpecifier();
                auto paramId = parseIdentifier();
                arguments.emplace_back(paramType, paramId);
            } while(match(TokenType::COMMA));
            consume(TokenType::RPAREN);
            auto body = parseCompoundStmt();
            return new FunctionDefinition(type, id, arguments, body);
        }
    } else {
        // else it is a var definition

        // array
        if(match(TokenType::LBRACKET)) {
            consume(TokenType::RBRACKET);
        } else if(match(TokenType::ASSIGN)) {

        }

        consume(TokenType::SEMICOLON);
    }
    return nullptr;
}

Expr *Parser::parseExpr() {
    return parseAssignmentExpr();
}

Expr *Parser::parseAssignmentExpr() {
    auto lvalue = parseUnaryExpr();
    consume(TokenType::ASSIGN);
    auto rvalue = parseExpr();
    return new Assignment(lvalue, rvalue);
}

Expr *Parser::parseUnaryExpr() {
    return nullptr;
}

void Parser::consume(TokenType type) {
    if (tokens[index].type == type) {
        index++;
    } else {
        std::cerr << "expect " << tokentype2string[type] << std::endl;
        exit(-1);
    }
}

bool Parser::match(TokenType type) {
    return tokens[index++].type == type;
}

TypeSpecifier *Parser::parseTypeSpecifier() {
    return nullptr;
}

Identifier * Parser::parseIdentifier() {
    return nullptr;
}

CompoundStatement *Parser::parseCompoundStmt() {
    return nullptr;
}

