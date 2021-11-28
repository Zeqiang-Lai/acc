#include "parser.h"
#include "type.h"

#include <iostream>
#include "error.h"

TranslationUnit *Parser::parse() {
    /*
     * Top level:
     *  StructDeclaration: Type
     *  FunctionDefinition: Type name(Type x, Type y) { body }
     *  GlobalVariable: Type x,y,z;
     */

    vector<Node *> declarations;
//    while (!match(TokenType::END)) {
//        Type *declType = parseTypeSpecifier();
//        if (match(TokenType::SEMICOLON)) { continue; }
//        do {
//            Node *declaration = parseFuncOrVariable(declType);
//            declarations.push_back(declaration);
//        } while (match(TokenType::COMMA));
//    }
    while (!match(TokenType::END)) {
        declarations.push_back(parseExpr());
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
        if (peek().type == TokenType::LBRACE) {
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

Token Parser::consume(TokenType type) {
    auto token = tokens[index];
    if (tokens[index].type == type) {
        index++;
        return token;
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

Node *Parser::parseFuncOrVariable(Type *baseType) {
    Identifier *id = parseIdentifier();

    // if start with '(', it is function
    if (match(TokenType::LPAREN)) {
        while (!match(TokenType::RPAREN)) {
            auto paramType = parseTypeSpecifier();
            auto paramID = parseIdentifier();
        }
        return nullptr;
    }

    // array definition
    if (match(TokenType::LBRACKET)) {

    }


    return nullptr;
}

Expr *Parser::parseExpr() {
    return parseAssignExpr();
}

Expr *Parser::parseAssignExpr() {
    // TODO: conditional expression
    Expr *expr = parseConditionalExpr();
    auto op = peek();
    if (isAssignOp(op.type)) {
        next();
        // check expr is unary
        Expr *rvalue = parseAssignExpr();
        return new Assignment(expr, rvalue);
    }
    return expr;
}

bool Parser::isAssignOp(TokenType type) {
    return type == TokenType::ASSIGN;
}


Expr *Parser::parseConditionalExpr() {
    return parseLogicalOrExpr();
}

BinaryOp Parser::convert2BinaryOp(TokenType type) {
    switch (type) {
        case TokenType::EQ:
            return BinaryOp::Equals;
        case TokenType::NEQ:
            return BinaryOp::NotEquals;
        case TokenType::GT:
            return BinaryOp::Greater;
        case TokenType::LT:
            return BinaryOp::Less;
        case TokenType::GEQ:
            return BinaryOp::GreaterOrEqual;
        case TokenType::LEQ:
            return BinaryOp::LessOrEqual;
        case TokenType::ADD:
            return BinaryOp::Plus;
        case TokenType::MINUS:
            return BinaryOp::Minus;
        case TokenType::MULTI:
            return BinaryOp::Multiply;
        case TokenType::DIV:
            return BinaryOp::Divide;
        case TokenType::MOD:
            return BinaryOp::Modulo;
        default:
            internal_error("invalid binary op");
    }
}

Expr *Parser::parseLogicalOrExpr() {
    Expr *expr = parseLogicalAndExpr();
    while (match(TokenType::LOGIC_OR)) {
        Expr *right = parseLogicalAndExpr();
        expr = new Binary(expr, right, BinaryOp::LogicalOr);
    }
    return expr;
}

Expr *Parser::parseLogicalAndExpr() {
    Expr *expr = parseEqualityExpr();
    while (match(TokenType::LOGIC_AND)) {
        Expr *right = parseEqualityExpr();
        expr = new Binary(expr, right, BinaryOp::LogicalAnd);
    }
    return expr;
}

Expr *Parser::parseEqualityExpr() {
    Expr *expr = parseRelationalExpr();
    while (isEqualityOp(peek().type)) {
        auto token = next();
        Expr *right = parseRelationalExpr();
        expr = new Binary(expr, right, convert2BinaryOp(token.type));
    }
    return expr;
}

bool Parser::isEqualityOp(TokenType type) {
    return type == TokenType::EQ || type == TokenType::NEQ;
}

Expr *Parser::parseRelationalExpr() {
    Expr *expr = parseAdditiveExpr();
    while (isRelationalOp(peek().type)) {
        auto token = next();
        Expr *right = parseAdditiveExpr();
        expr = new Binary(expr, right, convert2BinaryOp(token.type));
    }
    return expr;
}

bool Parser::isRelationalOp(TokenType type) {
    return type == TokenType::GT || type == TokenType::LT ||
           type == TokenType::GEQ || type == TokenType::LEQ;
}

Expr *Parser::parseAdditiveExpr() {
    Expr *expr = parseMultiplicativeExpr();
    while (isAdditiveOp(peek().type)) {
        auto token = next();
        Expr *right = parseMultiplicativeExpr();
        expr = new Binary(expr, right, convert2BinaryOp(token.type));
    }
    return expr;
}

bool Parser::isAdditiveOp(TokenType type) {
    return type == TokenType::ADD || type == TokenType::MINUS;
}

Expr *Parser::parseMultiplicativeExpr() {
    Expr *expr = parseCastExpr();
    while (isMultiplicativeOp(peek().type)) {
        auto token = next();
        Expr *right = parseCastExpr();
        expr = new Binary(expr, right, convert2BinaryOp(token.type));
    }
    return expr;
}

bool Parser::isMultiplicativeOp(TokenType type) {
    return type == TokenType::MULTI || type == TokenType::DIV ||
           type == TokenType::MOD;
}


Expr *Parser::parseCastExpr() {
    // TODO: support cast
    return parseUnaryExpr();
}

Expr *Parser::parseUnaryExpr() {
    auto token = peek();
    if (isUnaryOperator(token.type)) {
        next();
        Expr *expr = parseCastExpr();
        return new Unary(expr, convert2UnaryOp(token.type));
    }
    return parsePostfixExpr();
}

UnaryOp Parser::convert2UnaryOp(TokenType type) {
    switch (type) {
        case TokenType::ADD:
            return UnaryOp::Positive;
        case TokenType::MINUS:
            return UnaryOp::Negative;
        case TokenType::NOT:
            return UnaryOp::Not;
        default:
            internal_error("invalid type");
    }
}

bool Parser::isUnaryOperator(TokenType type) {
    return type == TokenType::ADD || type == TokenType::MINUS || type == TokenType::NOT;
}

Expr *Parser::parsePostfixExpr() {
    Expr *expr = parsePrimaryExpr();
    auto token = peek();
    if (token.type == TokenType::LBRACKET) {
        next();
        Expr *idx = parseExpr();
        consume(TokenType::RBRACKET);
        return new ArrayRef(expr, idx);
    }
    if (token.type == TokenType::LPAREN) {
        next();
        vector<Expr *> args;
        if (peek().type != TokenType::RPAREN) {
            do {
                args.push_back(parseExpr());
            } while (match(TokenType::COMMA));
        }
        consume(TokenType::RPAREN);
        return new FunCall(expr, args);
    }
    return expr;
}

Expr *Parser::parsePrimaryExpr() {
    auto token = next();
    Expr *expr = nullptr;
    switch (token.type) {
        case TokenType::ID:
            return new Identifier(token.string_value);
        case TokenType::LPAREN:
            expr = parseExpr();
            consume(TokenType::RPAREN);
            return expr;
        case TokenType::INT_CONST:
            return new Integer(token.int_value);
        default:
            return expr;
    }
}

Identifier *Parser::parseIdentifier() {
    return nullptr;
}

















// endregion
