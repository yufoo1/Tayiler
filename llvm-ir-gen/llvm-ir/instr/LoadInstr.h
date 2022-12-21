//
// Created by yufoo1 on 2022/12/13.
//

#ifndef TAYILER_LOADINSTR_H
#define TAYILER_LOADINSTR_H

#include "Instr.h"
#include "../BasicBlock.h"

class LoadInstr: public Instr {
private:
    Use* posUse = nullptr;
public:
    explicit LoadInstr(BasicBlock* parent, FuncType type, Value* posValue, int idx) {
        setSize(4);
        posUse = new Use(posValue);
        setFuncType(type);
        genInstrVirtualReg(idx);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return getVal() + " = load " + FuncType2String.at(getFuncType()) + ", " + FuncType2String.at(getFuncType()) + "* " + posUse->getValue()->getVal();
    }

    string toMipsString_stack(string ident) override {
        return "";
    }
};
#endif //TAYILER_LOADINSTR_H
