//
// Created by yufoo1 on 2022/10/28.
//

#ifndef TAYILER_CONSTANTINT_H
#define TAYILER_CONSTANTINT_H
#include "Constant.h"
#include "iostream"
#include "../Value.h"

class ConstantInt: public Constant {
public:
    explicit ConstantInt(const string& val) {
        setVal(val);
        setFuncType(FuncType::INT32);
    }

    int getIntVal() {
        return stoi(getVal());
    }
};
ConstantInt* CONSTANT_ZERO = new ConstantInt("0");
ConstantInt* CONSTANT_ONE = new ConstantInt("1");

#endif //TAYILER_CONSTANTINT_H
