//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_GETELEMENTPTR_H
#define TAYILER_GETELEMENTPTR_H

#include "Instr.h"
#include "../global-val/GlobalString.h"
#include "../BasicBlock.h"

class GetElementPtr: public Instr {
private:
    GlobalString* globalString;
public:
    explicit GetElementPtr(BasicBlock* parent, GlobalString* globalString) {
        genInstrVal();
        this->globalString = globalString;
        parent->addInstr(this);
    }

    string toString() {
        return getVal() + " = getelementptr inbounds " + "[" + globalString->getLenString() + " x " + globalString->getTypeString() + "], " + "[" + globalString->getLenString() + " x " + globalString->getTypeString() + "]* " + globalString->getLabel() + ", i32 0, i32 0";

    }
};
#endif //TAYILER_GETELEMENTPTR_H
