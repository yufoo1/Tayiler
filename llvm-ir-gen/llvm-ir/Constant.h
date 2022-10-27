//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_CONSTANT_H
#define TAYILER_CONSTANT_H

#include "Value.h"

class Constant: public Value {
public:

};
#endif //TAYILER_CONSTANT_H

class ConstantInt: public Constant {
private:
    int intVal;
public:
    explicit ConstantInt(string val) {
        intVal = stoi(val);
    }

    int getIntVal() {
        return intVal;
    }
};