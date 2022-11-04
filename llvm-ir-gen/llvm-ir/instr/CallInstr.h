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
    explicit CallInstr(BasicBlock* parent, Function* function, vector<Value*>* values, vector<AllocaInstr*>* allocaInstrs) {
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

    string toMipsString() override {
        string s;
        for (int i = 0; i < uses->size(); i++) {
            if (STACKPOSMAP.count(uses->at(i)->getValue())) {
                int srcPos = STACKPOSMAP.at(uses->at(i)->getValue());
                s += "\tlw $t0, " + to_string(srcPos) + "($sp)\n";
            } else {
                s += "\tori $t0, $0, " + uses->at(i)->getValue()->getVal() + "\n";
            }
            int tarPos = STACKPOSMAP.at(allocaInstrs->at(i));
            s += "\tsw $t0, " + to_string(tarPos) + "($sp)\n";
        }
        s += "\tjal " + function->getEntry()->getLabel() + "\n";
        return s;
    }

};
#endif //TAYILER_CALLINSTR_H
