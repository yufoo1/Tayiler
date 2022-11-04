//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_STOREINSTR_H
#define TAYILER_STOREINSTR_H

#include "Instr.h"

class StoreInstr: public Instr {
private:
    Use* tarUse = nullptr, * valUse = nullptr;
public:
    explicit StoreInstr(BasicBlock* parent, Value* tar, Value* val) {
        tarUse = new Use(tar);
        valUse = new Use(val);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return "store " + FuncType2String.at(valUse->getValue()->getFuncType()) + " " + valUse->getValue()->getVal() + ", " + FuncType2String.at(tarUse->getValue()->getFuncType()) + "* " + tarUse->getValue()->getVal();
    }

    string toMipsString() override {
        string s;
        if (valUse->getValue()->isInstr()) {
            int valPos = STACKPOSMAP.at(valUse->getValue());
            s += "\tlw $t0, " + to_string(valPos) + "($sp)\n";
        } else {
            s += "\tori $t0, $0, " + valUse->getValue()->getVal() + "\n";
        }
        int tarPos = STACKPOSMAP.at(tarUse->getValue());
        s += "\tsw $t0, " + to_string(tarPos) + "($sp)\n";
        return s;
    }
};
#endif //TAYILER_STOREINSTR_H
