//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_INSTR_H
#define TAYILER_INSTR_H

#include "../Use.h"
static string LOCAL_PREFIX = "%";
static string LOCAL_NAME_PREFIX = "v";
static int LOCAL_INSTR_CNT = 0;


class Instr: public Value {
public:
    Instr() { }

    virtual string toString() override { }

    virtual bool hasValue() { }

protected:

    void genInstrVal() {
        setVal(LOCAL_PREFIX + LOCAL_NAME_PREFIX + to_string(LOCAL_INSTR_CNT++));
    }
};

#endif //TAYILER_INSTR_H