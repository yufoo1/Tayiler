//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_SYMBOLTABLE_H
#define TAYILER_SYMBOLTABLE_H

#include "SymbolTerm.h"

class SymbolTable {
private:
    SymbolTable* parent;
    map<string, SymbolTerm*> terms;
public:
    explicit SymbolTable(SymbolTable* parent) {
        this->parent = parent;
    }

    SymbolTable* getParent() {
        return parent;
    }

    void addSymbolTerm(SymbolTerm* term) {
        terms.insert(pair<string, SymbolTerm*>(term->getIdent(), term));
    }

    bool checkDuplicated(string ident) {
        return terms.count(ident);
    }

    SymbolTerm* getSymbolTerm(string ident) {
        return terms.at(ident);
    }
};
#endif //TAYILER_SYMBOLTABLE_H
