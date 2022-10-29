//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_ALLOCAINSTR_H
#define TAYILER_ALLOCAINSTR_H

#include "Instr.h"
#include "../../symbol/SymbolTable.h"
#include "../../symbol/SymbolTerm.h"

class AllocaInstr: public Instr {
public:
    explicit AllocaInstr(BasicBlock* parent, SymbolTable* table, string ident, FuncType type, bool isConstant) {
        genInstrVal();
        setFuncType(type);
        table->addSymbolTerm(new SymbolTerm(ident, type, isConstant));
        parent->addInstr(this);
    }
    string toString() override {
        return getVal() + " = alloca " + getFuncTypeString();
    }
};
#endif //TAYILER_ALLOCAINSTR_H
