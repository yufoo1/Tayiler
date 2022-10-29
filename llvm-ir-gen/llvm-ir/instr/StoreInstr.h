//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_STOREINSTR_H
#define TAYILER_STOREINSTR_H

#include "Instr.h"

class StoreInstr: public Instr {
private:
    Use* tarUse, * valUse;
public:
    explicit StoreInstr(BasicBlock* parent, Value* tar, Value* val) {
        tarUse = new Use(tar);
        valUse = new Use(val);
        parent->addInstr(this);
    }

    string toString() override {
        return "store " + valUse->getValue()->getFuncTypeString() + " " + valUse->getValue()->getVal() + ", " + tarUse->getValue()->getFuncTypeString() + "* " + tarUse->getValue()->getVal();
    }
};
#endif //TAYILER_STOREINSTR_H
