//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_STOREINSTR_H
#define TAYILER_STOREINSTR_H

#include "Instr.h"

class StoreInstr: public Instr {
private:
    Use* tarUse = nullptr, * valUse = nullptr;
    Use* baseUse = nullptr, * offsetUse = nullptr;
    Use* posUse = nullptr; /* for llvm */
public:
    explicit StoreInstr(BasicBlock* parent, Value* tar, Value* val) {
        tarUse = new Use(tar);
        valUse = new Use(val);
        parent->addInstr(this);
    }

    explicit StoreInstr(BasicBlock* parent, Value* base, Value* offset, Value* val, Value* pos) {
        baseUse = new Use(base);
        offsetUse = new Use(offset);
        posUse = new Use(pos);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        if(tarUse != nullptr) {
            return "store " + FuncType2String.at(valUse->getValue()->getFuncType()) + " " + valUse->getValue()->getVal() + ", " + FuncType2String.at(tarUse->getValue()->getFuncType()) + "* " + tarUse->getValue()->getVal();
        } else {
            return "store " + FuncType2String.at(valUse->getValue()->getFuncType()) + " " + valUse->getValue()->getVal() + ", " + FuncType2String.at(posUse->getValue()->getFuncType()) + "* " + posUse->getValue()->getVal();
        }
    }

    string toMipsString_stack(string ident) override {
        string s;
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
        if(tarUse != nullptr) {
            int tarPos = GETPOS(ident, tarUse->getValue());
            if(POSMAPHASPOS(ident, tarUse->getValue())) {
                s += "\tsw $t0, " + to_string(tarPos) + "($t7)\n";
            } else {
                s += "\tsw $t0, " + to_string(tarPos) + "($sp)\n";
            }
        } else {
//            int offsetPos = GETPOS(ident, offsetUse->getValue());
//            if(POSMAPHASPOS(ident, offsetUse->getValue())) {
//                s += "\tlw $t2, " + to_string(offsetPos) + "($t7)\n";
//            } else {
//                s += "\tlw $t2, " + to_string(offsetPos) + "($sp)\n";
//            }
//            int allocaPos = GETPOS(ident, allocaUse->getValue());
//            if(POSMAPHASPOS(ident, allocaUse->getValue())) {
//                s += "\tlw $t1, " + to_string(allocaPos) + "($t7)\n";
//                s += "\tadd $t1, $t1, $t2\n";
//                s += "\tsw $t0, $t1($t7)\n";
//            } else {
//                s += "\tlw $t1, " + to_string(allocaPos) + "($sp)\n";
//                s += "\tadd $t1, $t1, $t2\n";
//                s += "\tsw $t0, $t1($sp)\n";
//            }
        }
        return s;
    }
};
#endif //TAYILER_STOREINSTR_H
