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
    explicit LoadInstr(BasicBlock* parent, FuncType type, Value* pos, int idx) {
        setSize(4);
        posUse = new Use(pos);
        setFuncType(type);
        genInstrVirtualReg(idx);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return getVal() + " = load " + FuncType2String.at(getFuncType()) + ", " + FuncType2String.at(getFuncType()) + "* " + posUse->getValue()->getVal();
    }

    string toMipsString_stack(string ident) override {
        string s;
        s += "# >>> load\n";
        if (posUse->getValue()->isInstr()) {
            int posPos = GETPOS(ident, posUse->getValue());
            if(POSMAPHASPOS(ident, posUse->getValue())) {
                s += "\tlw $t0, " + to_string(posPos) + "($t7)\n";
            } else {
                s += "\tlw $t0, " + to_string(posPos) + "($sp)\n";
            }
        } else {
            s += "\tori $t0, $0, " + posUse->getValue()->getVal() + "\n";
        }
        s += "\tlw $t0, 0($t0)\n";
        int rdPos = GETPOS(ident, this);
        if(POSMAPHASPOS(ident, this)) {
            s += "\tsw $t0, " + to_string(rdPos) + "($t7)\n";
        } else {
            s += "\tsw $t0, " + to_string(rdPos) + "($sp)\n";
        }
        s += "# <<< load\n";
        return s;
    }
};
#endif //TAYILER_LOADINSTR_H
