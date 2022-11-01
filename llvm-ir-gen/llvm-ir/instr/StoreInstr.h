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
        return "store " + FuncType2String.at(valUse->getValue()->getFuncType()) + " " + valUse->getValue()->getVal() + ", " + FuncType2String.at(tarUse->getValue()->getFuncType()) + "* " + tarUse->getValue()->getVal();
    }
};
#endif //TAYILER_STOREINSTR_H
