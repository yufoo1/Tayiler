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
    string ident;
    FuncType retType;
    vector<Use*>* uses;
public:
    explicit CallInstr(BasicBlock* parent, string ident, FuncType retType, const vector<Value*>& values) {
        setFuncType(retType);
        this->ident = move(ident);
        this->retType = retType;
        uses = new vector<Use*>;
        for (auto i : values) {
            uses->emplace_back(new Use(i));
        }
        parent->addInstr(this);
    }

    string toLlvmString() override {
        assert(retType == FuncType::VOID);
        string str = "call " + FuncType2String.at(retType) + " @" + ident + "(";
        for (int i = 0; i < uses->size(); i++) {
            if (i != 0) str += ", ";
            str += FuncType2String.at(uses->at(i)->getValue()->getFuncType()) + " " + uses->at(i)->getValue()->getVal();
        }
        str += ")";
        return str;
    }

    string toMipsString() override {
        return "";
    }

};
#endif //TAYILER_CALLINSTR_H
