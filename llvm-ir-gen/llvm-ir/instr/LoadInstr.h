//
// Created by yufoo1 on 2022/12/13.
//

#ifndef TAYILER_LOADINSTR_H
#define TAYILER_LOADINSTR_H

#include "Instr.h"
#include "../BasicBlock.h"

class LoadInstr: public Instr {
private:
    Use* posUse = nullptr; /* for llvm */
    Use* baseUse = nullptr, * offsetUse = nullptr;
public:
    explicit LoadInstr(BasicBlock* parent, FuncType type, Value* base, Value* offset, int idx, Value* pos) {
        setSize(4);
        posUse = new Use(pos);
        baseUse = new Use(base);
        offsetUse = new Use(offset);
        setFuncType(type);
        genInstrVirtualReg(idx);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return getVal() + " = load " + FuncType2String.at(getFuncType()) + ", " + FuncType2String.at(getFuncType()) + "* " + posUse->getValue()->getVal();
    }

    string toMipsString_stack(string ident) override {
        string s;
        int offsetPos = GETPOS(ident, offsetUse->getValue());
        if(POSMAPHASPOS(ident, offsetUse->getValue())) {
            s += "\tlw $t2, " + to_string(offsetPos) + "($t7)\n";
        } else {
            s += "\tlw $t2, " + to_string(offsetPos) + "($sp)\n";
        }
        s += "\tsll $t2, $t2, 2\n";
        int basePos = GETPOS(ident, baseUse->getValue());
        if(POSMAPHASPOS(ident, baseUse->getValue())) {
            s += "\taddi $t1, $t7, " + to_string(basePos) + "\n";
            s += "\tadd $t1, $t1, $t2\n";
            s += "\tlw $t0, 0($t1)\n";
        } else {
            s += "\taddi $t1, $sp, " + to_string(basePos) + "\n";
            s += "\tsub $t1, $t1, $t2\n";
            s += "\tlw $t0, 0($t1)\n";
        }
        int rdPos = GETPOS(ident, this);
        if(POSMAPHASPOS(ident, this)) {
            s += "\tsw $t0, " + to_string(rdPos) + "($t7)\n";
        } else {
            s += "\tsw $t0, " + to_string(rdPos) + "($sp)\n";
        }
        return s;
    }
};
#endif //TAYILER_LOADINSTR_H
