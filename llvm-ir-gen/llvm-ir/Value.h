//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_VALUE_H
#define TAYILER_VALUE_H
#include "set"

class Value {
private:
    FuncType funcType;
    string val;
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
            case FuncType::VOID: return "void";
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

    FuncType getFuncType() {
        return funcType;
    }

    virtual string getValueString() { }

    virtual string toString() { }

};
#endif //TAYILER_VALUE_H
