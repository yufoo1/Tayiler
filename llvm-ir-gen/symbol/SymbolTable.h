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

    SymbolTerm* getSymbolTerm(string ident) {
        auto* cur = this;
        while(cur != nullptr) {
            if(cur->getSymbolTerms()->count(ident)) {
                return cur->getSymbolTerms()->at(ident);
            } else {
                cur = cur->parent;
                continue;
            }
        }
        return nullptr;
    }

    map<string, SymbolTerm*>* getSymbolTerms() {
        return terms;
    }
};
#endif //TAYILER_SYMBOLTABLE_H
