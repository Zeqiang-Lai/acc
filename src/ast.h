//
// Created by 1 on 2021/7/4.
//

#ifndef ACC_AST_H
#define ACC_AST_H

#include <vector>

using namespace std;

class TranslationUnit;
class FunctionDefinition;
class Declaration;
class TypeSpecifier;

class Identifier;
class Constant;
class PrimaryExpr;
class PostfixExpr;
class UnaryExpr;
class CastExpr;
class MultiplicativeExpr;
class AdditiveExpr;
class ShiftExpr;
class RelationalExpr;
class EqualityExpr;
class AndExpr;
class ExclusiveOrExpr;
class InclusiveOrExpr;
class LogicalAndExpr;
class LogicalOrExpr;
class ConditionalExpr;
class AssignmentExpr;
class Expr;

class Statement;
class CompoundStatement;
class BlockItem; // statement | declaration
class ExprStatement;
class IfStatement;
class IterationStatement;
class JumpStatement;

class TranslationUnit {
public:
    vector<Declaration> declarations;
};

class TypeSpecifier {

};

class FunctionDefinition {

};

class Declaration {
public:
    TypeSpecifier type;
};



#endif //ACC_AST_H
