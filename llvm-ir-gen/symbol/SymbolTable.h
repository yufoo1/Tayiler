//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_SYMBOLTABLE_H
#define TAYILER_SYMBOLTABLE_H
class SymbolTable {
private:
    SymbolTable* parent;
public:
    explicit SymbolTable(SymbolTable* parent) {
        this->parent = parent;
    }

    SymbolTable* getParent() {
        return parent;
    }
};
#endif //TAYILER_SYMBOLTABLE_H
