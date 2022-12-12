//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_PUTSTRINSTR_H
#define TAYILER_PUTSTRINSTR_H

#include "Instr.h"
#include "../BasicBlock.h"

class PutstrInstr: public Instr {
private:
    Use* use = nullptr;
public:
    explicit PutstrInstr(BasicBlock* parent, Value* val) {
        this->setFuncType(FuncType::VOID);
        use = new Use(val);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return "call " + FuncType2String.at(getFuncType()) + " @putstr" + "(" +
               FuncType2String.at(use->getValue()->getFuncType()) + "* " + use->getValue()->getVal() + ")";
    }

    string toMipsString_stack(string ident) override {
        return "\tli $v0, 4\n\tsyscall\n";
    }
};
#endif //TAYILER_PUTSTRINSTR_H