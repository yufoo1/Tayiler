//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_STOREINSTR_H
#define TAYILER_STOREINSTR_H

#include "Instr.h"

class StoreInstr: public Instr {
private:
    Use* tarUse = nullptr, * valUse = nullptr;
public:
    explicit StoreInstr(BasicBlock* parent, Value* tar, Value* val) {
        tarUse = new Use(tar);
        valUse = new Use(val);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return "store " + FuncType2String.at(valUse->getValue()->getFuncType()) + " " + valUse->getValue()->getVal() + ", " + FuncType2String.at(tarUse->getValue()->getFuncType()) + "* " + tarUse->getValue()->getVal();
    }

    string toMipsString_stack(string ident) override {
        string s;
        s += "# >>> store\n";
        if (valUse->getValue()->isInstr()) {
            int valPos = GETPOS(ident, valUse->getValue());
            if(POSMAPHASPOS(ident, valUse->getValue())) {
                s += "\tlw $t0, " + to_string(valPos) + "($t7)\n";
            } else {
                s += "\tlw $t0, " + to_string(valPos) + "($sp)\n";
            }
        } else {
            s += "\tori $t0, $0, " + valUse->getValue()->getVal() + "\n";
        }
        int tarPos = GETPOS(ident, tarUse->getValue());
        if(tarUse->getValue()->getIsGetElementPtrInstr()) {
            if (tarUse->getValue()->isInstr()) {
                int posPos = GETPOS(ident, tarUse->getValue());
                if(POSMAPHASPOS(ident, tarUse->getValue())) {
                    s += "\tlw $t1, " + to_string(posPos) + "($t7)\n";
                } else {
                    s += "\tlw $t1, " + to_string(posPos) + "($sp)\n";
                }
            } else {
                s += "\tori $t1, $0, " + tarUse->getValue()->getVal() + "\n";
            }
            s += "\tsw $t0, 0($t1)\n";
        } else {
            if(POSMAPHASPOS(ident, tarUse->getValue())) {
                s += "\tsw $t0, " + to_string(tarPos) + "($t7)\n";
            } else {
                s += "\tsw $t0, " + to_string(tarPos) + "($sp)\n";
            }
        }
        s += "# <<< store\n";
        return s;
    }
};
#endif //TAYILER_STOREINSTR_H
