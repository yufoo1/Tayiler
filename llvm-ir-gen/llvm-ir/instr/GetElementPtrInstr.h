//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_GETELEMENTPTRINSTR_H
#define TAYILER_GETELEMENTPTRINSTR_H

#include "Instr.h"
#include "../global-val/GlobalString.h"
#include "../BasicBlock.h"

class GetElementPtrInstr: public Instr {
private:
    GlobalString* globalString;
public:
    explicit GetElementPtrInstr(BasicBlock* parent, GlobalString* globalString, int idx) {
        genInstrVal(idx);
        this->setFuncType(FuncType::INT8);
        this->globalString = globalString;
        parent->addInstr(this);
    }

    string toString() {
        return getVal() + " = getelementptr inbounds " + "[" + globalString->getLenString() + " x " + globalString->getTypeString() + "], " + "[" + globalString->getLenString() + " x " + globalString->getTypeString() + "]* " + globalString->getLabel() + ", i32 0, i32 0";

    }
};
#endif //TAYILER_GETELEMENTPTRINSTR_H
