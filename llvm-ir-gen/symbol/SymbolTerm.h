//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_SYMBOLTERM_H
#define TAYILER_SYMBOLTERM_H

#include "../llvm-ir/instr/Instr.h"

class SymbolTerm {
private:
    string ident;
    FuncType type;
    bool isConstant = false;
    Instr* allocaInstr = nullptr;
    int dimensionality;
    ConstExpNode* constExp = nullptr;

public:
    SymbolTerm(string ident, FuncType type, bool isConstant, int dimensionality, Instr* allocaInstr) {
        this->ident = std::move(ident);
        this->type = type;
        this->isConstant = isConstant;
        this->dimensionality = dimensionality;
        this->allocaInstr = allocaInstr;
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
        return allocaInstr;
    }

    void setConstExp(ConstExpNode* constExp) {
        this->constExp = constExp;
    }

    ConstExpNode* getConstExp() {
        return constExp;
    }

};
#endif //TAYILER_SYMBOLTERM_H
