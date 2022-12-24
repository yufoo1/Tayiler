#include <utility>

//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_VALUE_H
#define TAYILER_VALUE_H
class Value {
private:
    FuncType funcType;
    string val;
    bool isGetElementPtrInstr = false;
public:
    explicit Value(FuncType type) {
        this->funcType = type;
    }

    explicit Value() = default;

    string getVal() {
        return val;
    }

    void setVal(string val) {
        this->val = std::move(val);
    }

    void setFuncType(FuncType type) {
        this->funcType = type;
    }

    FuncType getFuncType() {
        return funcType;
    }

    bool getIsGetElementPtrInstr() {
        return isGetElementPtrInstr;
    }

    void setIsGetElementPtrInstr(bool isGetElementPtrInstr) {
        this->isGetElementPtrInstr = isGetElementPtrInstr;
    }

    virtual string toLlvmString() { return ""; }

    virtual string toMipsString() { return ""; }

    virtual string toMipsString_stack(string ident) { return ""; }

    virtual bool isInstr() { return false; };

    virtual bool judgeFromPosMap(string ident) { return false; };
};
#endif //TAYILER_VALUE_H
