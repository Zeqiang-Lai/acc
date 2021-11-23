#include "parser.h"
#include "type.h"

#include <iostream>

TranslationUnit *Parser::parse() {
    vector<Node *> declarations;
    while (!match(TokenType::END)) {
        Type *declType = parseTypeSpecifier();
        if(match(TokenType::SEMICOLON)) { continue; }
        do {

        } while (match(TokenType::COMMA));
    }
    return new TranslationUnit(declarations);
}

// region: Declaration

Type *Parser::parseTypeSpecifier() {
    Token token = next();
    switch (token.type) {
        case TokenType::INT:
            return &PrimitiveType::Int;
        case TokenType::VOID:
            return &PrimitiveType::Void;
        case TokenType::CHAR:
            return &PrimitiveType::Char;
        case TokenType::DOUBLE:
            return &PrimitiveType::Double;
        case TokenType::STRUCT:
            return parseStruct();
        case TokenType::ID:
            // unknown type name '#'
            break;
        default:
            // expect external declaration
            break;
    }
}

Type *Parser::parseStruct() {
    Token token = next();
    if (token.type == TokenType::ID) {
        if(peek().type == TokenType::LBRACE) {
            // definition
            next();
            return parseStructDeclarationList(&token);
        } else {
            // declaration of struct
        }
    } else if (token.type == TokenType::LBRACE) {
        // anonymous struct
        return parseStructDeclarationList(nullptr);
    }
    // error: Declaration of anonymous struct must be a definition
}

Type *Parser::parseStructDeclarationList(Token *id) {

    return nullptr;
}

// endregion

// region Utils

void Parser::consume(TokenType type) {
    if (tokens[index].type == type) {
        index++;
    } else {
        std::cerr << "expect " << tokentype2string[type] << std::endl;
        exit(-1);
    }
}

bool Parser::match(TokenType type) {
    if (tokens[index].type == type) {
        index++;
        return true;
    }
    return false;
}

Token Parser::peek() {
    return tokens[index];
}

Token Parser::next() {
    return tokens[index++];
}

// endregion
