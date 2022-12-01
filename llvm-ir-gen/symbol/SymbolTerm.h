//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_SYMBOLTERM_H
#define TAYILER_SYMBOLTERM_H

//#include "../llvm-ir/instr/AllocaInstr.h"

#include "../llvm-ir/instr/Instr.h"

class SymbolTerm {
private:
    string ident;
    FuncType type;
    bool isConstant = false;
    Instr* instr;
    int dimensionality;

public:
    SymbolTerm(string ident, FuncType type, bool isConstant, int dimensionality/* , AllocaInstr* instr */) {
        this->ident = std::move(ident);
        this->type = type;
        this->isConstant = isConstant;
        this->dimensionality = dimensionality;
//        this->instr = instr;
    }

    string getIdent() {
        return ident;
    }

    FuncType getFuncType() {
        return type;
    }

    bool getIsConstant() {
        return isConstant;
    }

    int getDimensionality() {
        return dimensionality;
    }

    Instr* getAllocaInstr() {
        return instr;
    }

};
#endif //TAYILER_SYMBOLTERM_H
