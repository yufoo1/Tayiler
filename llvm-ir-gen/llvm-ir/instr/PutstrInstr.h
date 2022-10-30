//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_PUTSTRINSTR_H
#define TAYILER_PUTSTRINSTR_H

#include "Instr.h"
#include "../BasicBlock.h"

class PutstrInstr: public Instr {
private:
    Use* use;
public:
    explicit PutstrInstr(BasicBlock* parent, Value* val) {
        this->setFuncType(FuncType::VOID);
        use = new Use(val);
        parent->addInstr(this);
    }

    string toString() override {
        return "call " + getFuncTypeString() + " @putstr" + "(" +
               FuncType2String.at(use->getValue()->getFuncType()) + " " + use->getValue()->getVal() + ")";
    }
};
#endif //TAYILER_PUTSTRINSTR_H