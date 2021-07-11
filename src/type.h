//
// Created by 1 on 2021/7/10.
//

#ifndef ACC_TYPE_H
#define ACC_TYPE_H

#include <map>
#include <string>
#include <utility>

class Type {

};

enum class PrimitiveTypeTag {
    VOID, CHAR, INT, DOUBLE
};

class PrimitiveType : public Type {
    PrimitiveTypeTag tag;
    explicit PrimitiveType(PrimitiveTypeTag tag) : tag(tag) {}

public:
    static PrimitiveType Void, Char, Int, Double;
};

class StructType : public Type {
    std::map<std::string, Type&> fields;

public:
    StructType(std::map<std::string, Type &> fields) : fields(std::move(fields)) {}

    Type& field(const std::string& name) { return fields[name]; }
};

class ArrayType : public Type {
public:
    Type elementType;

    ArrayType(const Type &elementType) : elementType(elementType) {}
};

class PointerType : public Type {
public:
    Type elementType;

    PointerType(const Type &elementType) : elementType(elementType) {}
};

#endif //ACC_TYPE_H
