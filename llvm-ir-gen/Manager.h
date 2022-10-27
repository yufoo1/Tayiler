//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_MANAGER_H
#define TAYILER_MANAGER_H


#include "symbol/SymbolTable.h"
#include "llvm-ir/Function.h"

class Manager {
public:
    explicit Manager() {
    }

    SymbolTable getSymbolTable() {
        return symbolTable;
    }

    void addFunction(Function* function) {
        functions.insert({function->getIdent(), function});
    }

    void outputLLVM(const char *outputFile) {
        ofstream f(outputFile);
        for (auto i : functions) {
            if (i.second->hasEntry()) {
                f << i.second->getOutputString() << endl;
                cout << i.second->getOutputString() << endl;
            }
        }
        f.close();
    }

private:
    SymbolTable symbolTable = SymbolTable(nullptr);
    map<string, Function*> functions;
};
#endif //TAYILER_MANAGER_H
