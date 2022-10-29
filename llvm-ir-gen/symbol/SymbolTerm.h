//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_SYMBOLTERM_H
#define TAYILER_SYMBOLTERM_H

//#include "../llvm-ir/instr/AllocaInstr.h"

class SymbolTerm {
private:
    string ident;
    FuncType type;
    bool isConstant = false;
//    AllocaInstr* instr;

public:
    SymbolTerm(string ident, FuncType type, bool isConstant/* , AllocaInstr* instr */) {
        this->ident = ident;
        this->type = type;
        this->isConstant = isConstant;
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

//    AllocaInstr* getAllocaInstr() {
//        return instr;
//    }

};
#endif //TAYILER_SYMBOLTERM_H
