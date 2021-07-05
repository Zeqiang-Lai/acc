//
// Created by 1 on 2021/7/4.
//

#ifndef ACC_PARSER_H
#define ACC_PARSER_H

#include <vector>
#include "token.h"
#include "ast.h"

class Parser {
public:
    explicit Parser(const vector<Token>& tokens) : tokens(tokens) {}
    TranslationUnit parse();

private:
    const vector<Token>& tokens;
};


#endif //ACC_PARSER_H
