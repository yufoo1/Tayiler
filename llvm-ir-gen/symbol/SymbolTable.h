//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_SYMBOLTABLE_H
#define TAYILER_SYMBOLTABLE_H

#include "SymbolTerm.h"
#include "../llvm-ir/instr/Instr.h"

class SymbolTable {
private:
    SymbolTable* parent = nullptr;
    map<string, SymbolTerm*>* terms = nullptr;
public:
    explicit SymbolTable(SymbolTable* parent) {
        this->parent = parent;
        this->terms = new map<string, SymbolTerm*>;
    }

    SymbolTable* getParent() {
        return parent;
    }

    void addSymbolTerm(SymbolTerm* term) {
        terms->insert(pair<string, SymbolTerm*>(term->getIdent(), term));
    }

    bool hasSymbolTerm(string ident) {
        return terms->count(ident);
    }

    SymbolTerm* getSymbolTerm(string ident) {
        return terms->at(ident);
    }

    map<string, SymbolTerm*>* getSymbolTerms() {
        return terms;
    }

//    map<string, Instr*>* getAllocaInstrs() {
//        return allocaInstrs;
//    }
};
#endif //TAYILER_SYMBOLTABLE_H
