//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_PUTINTINSTR_H
#define TAYILER_PUTINTINSTR_H

#include "Instr.h"
#include "../BasicBlock.h"

class PutintInstr: public Instr{
private:
    Use* use = nullptr;
public:
    explicit PutintInstr(BasicBlock* parent, Value* val) {
        this->use = new Use(val);
        this->setFuncType(FuncType::INT32);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return "call void @putint(" +
               FuncType2String.at(use->getValue()->getFuncType()) + " " + use->getValue()->getVal() + ")";
    }

    string toMipsString_stack(string ident) override {
        int pos = GETPOS(ident, use->getValue());
        if(POSMAPHASPOS(ident, use->getValue())) {
            return "\tlw $a0, " + to_string(pos) + "($t7)\n\tli $v0, 1\n\tsyscall\n";
        } else {
            return "\tlw $a0, " + to_string(pos) + "($sp)\n\tli $v0, 1\n\tsyscall\n";
        }
    }
};
#endif //TAYILER_PUTINTINSTR_H
