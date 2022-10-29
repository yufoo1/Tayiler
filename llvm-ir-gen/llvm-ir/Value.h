//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_VALUE_H
#define TAYILER_VALUE_H
#include "set"
enum class ValueType {
    ALUINSTR, RETURNINSTR, CONSTANTINT
};

class Value {
private:
    FuncType funcType;
    string val;
    ValueType valueType;
public:
    Value(FuncType type) {
        this->funcType = type;
    }

    Value() {

    }

    string getFuncTypeString() {
        switch (funcType) {
            case FuncType::INT1: return "i1";
            case FuncType::INT32: return "i32";
            default: break;
        }
    }

    string getVal() {
        return val;
    }

    void setVal(string val) {
        this->val = val;
    }

    void setFuncType(FuncType type) {
        this->funcType = type;
    }

    void setValueType(ValueType type) {
        this->valueType = type;
    }

    FuncType getFuncType() {
        return funcType;
    }

    ValueType getValueType() {
        return valueType;
    }

    virtual string getValueString() { }

    virtual string toString() { }

};
#endif //TAYILER_VALUE_H
