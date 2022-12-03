//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_INSTR_H
#define TAYILER_INSTR_H

#include "../Use.h"
static string LOCAL_PREFIX = "%";
static string LOCAL_NAME_PREFIX = "v";
static map<Value*, int> STACKPOSMAP;
static void ALLOCSTACK(Value* value) {
    STACKPOSMAP.insert({value, STACKPOSMAP.size() * (-4)});
}
class Instr: public Value {
public:
    Instr() = default;

    virtual string toLlvmString() override { return 0; }

    virtual string toMipsString() override { return 0; }

    virtual bool hasValue() { return 0; }

protected:

    void genInstrVirtualReg(int idx) {
        setVal(LOCAL_PREFIX + LOCAL_NAME_PREFIX + to_string(idx));
    }
public:
    bool isInstr() override {
        return true;
    }
};

#endif //TAYILER_INSTR_H