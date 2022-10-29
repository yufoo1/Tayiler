//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_INSTR_H
#define TAYILER_INSTR_H

#include "../Value.h"
#include "../BasicBlock.h"
#include "../Use.h"
static string LOCAL_PREFIX = "%";
static string LOCAL_NAME_PREFIX = "v";
static int LOCAL_INSTR_CNT = 0;

class BasicBlock;

class Instr: public Value {
public:
    Instr() { }

    virtual string toString() override { }

    virtual bool hasValue() { }
};

#endif //TAYILER_INSTR_H