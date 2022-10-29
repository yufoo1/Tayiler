//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_CALLINSTR_H
#define TAYILER_CALLINSTR_H

#include "Instr.h"
#include "../BasicBlock.h"

class CallInstr: public Instr {
private:
    Use* use;
    CallInstrType type;
public:
    explicit CallInstr(BasicBlock* parent, Value* val, CallInstrType type) {
        this->use = new Use(val);
        this->type = type;
        switch (type) {
            case CallInstrType::GETINT: setFuncType(FuncType::INT32); break;
            default: break;
        }
        parent->addInstr(this);
    }

    string toString() override {
        return "call " + FuncType2String.at(this->getFuncType()) + " @" + CallInstrType2String.at(type) + "(" +
        FuncType2String.at(use->getValue()->getFuncType()) + " " + use->getValue()->getVal() + ")";
    }
};
#endif //TAYILER_CALLINSTR_H
