//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_ALLOCAINSTR_H
#define TAYILER_ALLOCAINSTR_H

#include "Instr.h"

#include <utility>
#include "../../symbol/SymbolTable.h"
#include "../../symbol/SymbolTerm.h"
class AllocaInstr: public Instr {
private:
    string ident;
    bool isParam; /* when is param, no need to output this alloca instr. */
    SymbolTable* table;
public:
    explicit AllocaInstr(BasicBlock* parent, SymbolTable* table, string ident, FuncType type, bool isConstant, bool isParam, int idx) {
        genInstrVirtualReg(idx);
        setFuncType(type);
        this->table = table;
        this->isParam = isParam;
        this->ident = std::move(ident);
        if (parent != nullptr) parent->addInstr(this);
    }

    string getIdent() {
        return ident;
    }

    string toLlvmString() override {
        if(isParam) {
            return "";
        } else {
            if(table->getSymbolTerm(ident)->getDimensionality() == 0) {
                return getVal() + " = alloca " + FuncType2String.at(getFuncType());
            } else {
//                string s
//                for(int i = 0; i < table->getSymbolTerm(ident)->getDimensionality(); ++i) {
//                    s += [ x
//                }
            }
        }
    }

    string toMipsString_stack(string ident) override {
        return "";
    }
};
#endif //TAYILER_ALLOCAINSTR_H
