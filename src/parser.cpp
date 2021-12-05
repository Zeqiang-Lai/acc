#include "parser.h"
#include "type.h"

#include <iostream>
#include "diagnostic.h"

TranslationUnit *Parser::parse() {
    /*
     * Top level:
     *  StructDef: Type
     *  FuncDef: Type name(Type x, Type y) { body }
     *  VarDef(global): Type x,y,z;
     */

    std::vector<Node *> defs;
    while (!match(TokenType::END)) {
        Type *baseType = parseTypeSpecifier();
        if (match(TokenType::SEMICOLON)) { continue; } // incomplete def

        // struct
        if (baseType->isStructType() && peek().type == TokenType::LBRACE) {
            auto *type = static_cast<StructType *>(baseType);
            parseStructDef(type);
            continue;
        }

        auto id = consume(TokenType::ID);

        // function
        if (peek().type == TokenType::LPAREN) {
            defs.push_back(parseFuncDef(baseType, id));;
            continue;
        }

        // global variable
        do {
            defs.push_back(parseVarDef(baseType, id));
        } while (match(TokenType::COMMA));
        consume(TokenType::SEMICOLON);
    }
    return new TranslationUnit(defs);
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
    }
    if (token.type == TokenType::STRUCT) {
        auto id = consume(TokenType::ID);
        if (!structMap.contains(id.string_value)) {
            auto type = new StructType(id.string_value);
            type->complete = false;
            structMap[id.string_value] = type;
        }
        return structMap[id.string_value];
    } else {
        // expect external declaration
        internal_error("expect type specifier");
    }
}

void Parser::parseStructDef(StructType *baseType) {
    if (baseType->complete) {
        internal_error("duplicate struct definition of %s", baseType->name.c_str());
    }
    next(); // consume '{'
    while (!match(TokenType::RBRACE)) {
        auto type = parseTypeSpecifier();
        do {
            auto id = consume(TokenType::ID);
            auto def = parseVarDef(type, id);
            baseType->fields[def->name] = def->type;
        } while (match(TokenType::COMMA));
        consume(TokenType::SEMICOLON);
    }
    consume(TokenType::SEMICOLON);
}

FuncDef *Parser::parseFuncDef(Type *returnType, const Token &id) {
    next(); // consume (
    std::map<std::string, Type *> paramTypes;
    if (!match(TokenType::RPAREN)) {
        do {
            auto type = parseTypeSpecifier();
            auto id = consume(TokenType::ID);
            auto param = parseVarDef(type, id);
            paramTypes[id.string_value] = param->type;
        } while (match(TokenType::COMMA));
        consume(TokenType::RPAREN);
    }
    CompoundStmt *body = parseCompoundStmt();
    return new FuncDef(id.string_value, body, returnType, paramTypes);
}

VarDef *Parser::parseVarDef(Type *baseType, const Token &id) {
    Expr *init = nullptr;
    if (match(TokenType::ASSIGN)) {
        init = parseExpr();
    }
    return new VarDef(id.string_value, init, baseType);
}

// endregion

// region Utils

Token Parser::consume(TokenType type) {
    auto token = tokens[index];
    if (tokens[index].type == type) {
        next();
        return token;
    } else {
        std::cerr << "expect " << tokentype2string[type] << std::endl;
        exit(-1);
    }
}

bool Parser::match(TokenType type) {
    if (tokens[index].type == type) {
        next();
        return true;
    }
    return false;
}

Token Parser::peek() {
    return tokens[index];
}

Token Parser::next() {
    auto token = tokens[index];
    index = std::min(index + 1, int(tokens.size()));
    return token;
}

// endregion


// region Expr

Expr *Parser::parseExpr() {
    return parseAssignExpr();
}

Expr *Parser::parseAssignExpr() {
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
    // TODO: conditional expression
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
        std::vector<Expr *> args;
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
    auto token = peek();
    consume(TokenType::ID);
    return new Identifier(token.string_value);
}

// endregion


// region stmt

Stmt *Parser::parseIfStmt() {
    consume(TokenType::IF);
    consume(TokenType::LPAREN);
    Expr *cond = parseExpr();
    consume(TokenType::RPAREN);
    CompoundStmt *thenbody = parseCompoundStmt();
    CompoundStmt *elsebody = nullptr;
    if (peek().type == TokenType::ELSE) {
        next();
        elsebody = parseCompoundStmt();
    }
    return new IfStmt(cond, thenbody, elsebody);
}

CompoundStmt *Parser::parseCompoundStmt() {
    consume(TokenType::LBRACE);
    std::vector<Node *> items;
    while (!match(TokenType::RBRACE) && !match(TokenType::END)) {
        switch (peek().type) {
            case TokenType::IF:
                items.push_back(parseIfStmt());
                continue;
            case TokenType::LBRACE:
                items.push_back(parseCompoundStmt());
                continue;
            case TokenType::RETURN:
                items.push_back(parseReturnStmt());
                continue;
        }
        if (peek().type == TokenType::INT || peek().type == TokenType::VOID ||
            peek().type == TokenType::CHAR || peek().type == TokenType::DOUBLE ||
            peek().type == TokenType::STRUCT) {
            Type *baseType = parseTypeSpecifier();
            if (match(TokenType::SEMICOLON)) { continue; } // incomplete def
            auto id = consume(TokenType::ID);
            do {
                items.push_back(parseVarDef(baseType, id));
            } while (match(TokenType::COMMA));
            consume(TokenType::SEMICOLON);
        } else {
            items.push_back(parseExprStmt());
        }
    }
    return new CompoundStmt(items);
}

Stmt *Parser::parseExprStmt() {
    Expr *expr = parseExpr();
    consume(TokenType::SEMICOLON);
    return new ExprStmt(expr);
}

Stmt *Parser::parseReturnStmt() {
    next();
    Expr *value = nullptr;
    if (peek().type != TokenType::SEMICOLON) {
        value = parseExpr();
    }
    consume(TokenType::SEMICOLON);
    return new ReturnStmt(value);
}

// endregion

// endregion
