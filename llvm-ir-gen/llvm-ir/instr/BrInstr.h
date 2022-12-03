//
// Created by yufoo1 on 2022/10/31.
//

#ifndef TAYILER_BRINSTR_H
#define TAYILER_BRINSTR_H

#include "Instr.h"
#include "../BasicBlock.h"

class BrInstr: public Instr {
private:
    Use* useSrc = nullptr;
    BasicBlock* trueBasicBlock = nullptr;
    BasicBlock* falseBasicBlock = nullptr;
public:
    explicit BrInstr(BasicBlock* parent, BasicBlock* trueBasicBlock) {
        this->trueBasicBlock = trueBasicBlock;
        setFuncType(FuncType::VOID);
        parent->addInstr(this);
    }

    explicit BrInstr(BasicBlock* parent, Value* src, BasicBlock* trueBasicBlock, BasicBlock* falseBasicBlock) {
        this->trueBasicBlock = trueBasicBlock;
        this->falseBasicBlock = falseBasicBlock;
        setFuncType(FuncType::VOID);
        useSrc = new Use(src);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        if (useSrc == nullptr) {
            return "br label " + trueBasicBlock->getLabel();
        } else {
            return "br i1 " + useSrc->getValue()->getVal() + ", label " + trueBasicBlock->getLabel() + ", label " + falseBasicBlock->getLabel();
        }
    }

    string toMipsString() override {
        return "";
    }
};
#endif //TAYILER_BRINSTR_H
