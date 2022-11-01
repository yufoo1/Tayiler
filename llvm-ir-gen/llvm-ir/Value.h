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
    explicit Value(FuncType type) {
        this->funcType = type;
    }

    explicit Value() = default;

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

    virtual string toString() { }

};
#endif //TAYILER_VALUE_H
