//
// Created by yufoo1 on 2022/10/31.
//

#ifndef TAYILER_CALLINSTR_H
#define TAYILER_CALLINSTR_H

#include "Instr.h"

#include <utility>
#include "../BasicBlock.h"
class CallInstr: public Instr {
private:
    Function* function = nullptr;
    vector<Use*>* uses = nullptr;
    vector<AllocaInstr*>* allocaInstrs = nullptr;
public:
    explicit CallInstr(BasicBlock* parent, Function* function, vector<Value*>* values, vector<AllocaInstr*>* allocaInstrs, int idx) {
        if(function->getRetType() != FuncType::VOID) {
            setSize(4);
        }
        genInstrVirtualReg(idx);
        setFuncType(function->getRetType());
        this->function = function;
        this->uses = new vector<Use*>;
        for (auto i : *values) {
            this->uses->emplace_back(new Use(i));
        }
        this->allocaInstrs = allocaInstrs;

        parent->addInstr(this);
    }

    string toLlvmString() override {
        string str;
        if (function->getRetType() != FuncType::VOID) {
            str += getVal() + " = ";
        }
        str += "call " + FuncType2String.at(function->getRetType()) + " @" + function->getIdent() + "(";
        for (int i = 0; i < uses->size(); i++) {
            if (i != 0) str += ", ";
            str += FuncType2String.at(uses->at(i)->getValue()->getFuncType()) + " " + uses->at(i)->getValue()->getVal();
        }
        str += ")";
        return str;
    }

    string toMipsString_stack(string ident) override {
        string s;
        s += "# >>> call\n";
        for (int i = 0; i < uses->size(); ++i) {
            if (MAINPOSMAPHASPOS(uses->at(i)->getValue()) || POSMAPHASPOS(ident, uses->at(i)->getValue())) {
                int srcPos = GETPOS(ident, uses->at(i)->getValue());
                if(POSMAPHASPOS(ident, uses->at(i)->getValue())) {
                    s += "\tlw $t0, " + to_string(srcPos) + "($t7)\n";
                } else {
                    s += "\tlw $t0, " + to_string(srcPos) + "($sp)\n";
                }
            } else {
                s += "\tori $t0, $0, " + uses->at(i)->getValue()->getVal() + "\n";
            }
            int tarPos = GETPOS(function->getIdent(), allocaInstrs->at(i));
            s += "\tsw $t0, -" + to_string(POSMAP.at(function->getIdent())->size() * 4 + 4 - tarPos) + "($t7)\n";
        }
        s += "\tsubi $t7, $t7, 4\n";
        s += "\tsw $ra, 0($t7)\n";
        s += "\tsubi $t7, $t7 " + to_string(POSMAP.at(function->getIdent())->size() * 4) + "\n";
        s += "\tjal " + function->getEntry()->getLabel() + "\n";
        s += "\taddi $t7, $t7 " + to_string(POSMAP.at(function->getIdent())->size() * 4) + "\n";
        s += "\tlw $ra, 0($t7)\n";
        s += "\taddi $t7, $t7, 4\n";
        if(function->getRetType() != FuncType::VOID) {
            int rdPos = GETPOS(ident, this);
            if(POSMAPHASPOS(ident, this)) {
                s += "\tsw $v0, " + to_string(rdPos) + "($t7)\n";
            } else {
                s += "\tsw $v0, " + to_string(rdPos) + "($sp)\n";
            }
        }
        s += "# <<< call\n";
        return s;
    }
};
#endif //TAYILER_CALLINSTR_H
