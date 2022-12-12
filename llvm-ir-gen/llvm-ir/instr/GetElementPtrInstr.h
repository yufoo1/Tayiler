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
    GlobalString* globalString = nullptr;
public:
    explicit GetElementPtrInstr(BasicBlock* parent, GlobalString* globalString, int idx) {
        genInstrVirtualReg(idx);
        this->setFuncType(FuncType::INT8);
        this->globalString = globalString;
        parent->addInstr(this);
    }

    string toLlvmString() {
        return getVal() + " = getelementptr inbounds " + "[" + to_string(globalString->getStr().length()) + " x " + FuncType2String.at(globalString->getFuncType()) + "], " + "[" +
                to_string(globalString->getStr().length()) + " x " + FuncType2String.at(globalString->getFuncType()) + "]* " + globalString->getPrefix() + globalString->getLabel() + ", i32 0, i32 0";
    }

    string toMipsString_stack(string ident) {
        return "\tla $a0, " + globalString->getLabel() + "\n";
    }
};
#endif //TAYILER_GETELEMENTPTRINSTR_H
