//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_MANAGER_H
#define TAYILER_MANAGER_H


#include "symbol/SymbolTable.h"
#include "llvm-ir/Function.h"
#include "llvm-ir/global-val/GlobalString.h"

class Manager {
public:
    explicit Manager() = default;

    SymbolTable getSymbolTable() {
        return symbolTable;
    }

    void addFunction(Function* function) {
        functions.insert({function->getIdent(), function});
    }

    void dumpLLVM(const char *outputFile) {
        ofstream f(outputFile);
        cout << "declare i32 @getint()\ndeclare void @putint(i32)\ndeclare void @putstr(i8*)\n" << endl;
        for (auto i : GLOBALSTRINGS) {
            cout << i->getLabel() + " = constant " + "[" + i->getLenString() + " x " + i->getTypeString() + "] c\"" + i->getStr() + "\"" << endl;
        }
        cout << endl;
        for (auto i : functions) {
            if (i.second->hasEntry()) {
                f << i.second->getValueString() << endl;
                cout << i.second->getValueString() << endl;
            }
        }
        f.close();
    }

private:
    SymbolTable symbolTable = SymbolTable(nullptr);
    map<string, Function*> functions;
};
#endif //TAYILER_MANAGER_H
