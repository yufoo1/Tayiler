//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_MANAGER_H
#define TAYILER_MANAGER_H


#include "../llvm-ir-gen/symbol/SymbolTable.h"
#include "../llvm-ir-gen/llvm-ir/Function.h"
#include "../llvm-ir-gen/llvm-ir/global-val/GlobalString.h"
#include "../utils/handler.h"

class Manager {
public:
    explicit Manager() = default;

    SymbolTable getSymbolTable() {
        return symbolTable;
    }

    void addFunction(Function* function) {
        functions.insert({function->getIdent(), function});
    }

    void dumpLlvm(ofstream* f) {
        *f << "declare i32 @getint()\ndeclare void @putint(i32)\ndeclare void @putstr(i8*)\n" << endl;
        for (auto i : GLOBALSTRINGS) {
            *f << i->toLlvmString() << endl;
        }
        cout << endl;
        for (auto i : functions) {
            if (i.second->hasEntry()) {
                *f << i.second->toLlvmString() << endl;
            }
        }
        if (mainFunction->hasEntry()) {
            *f << mainFunction->toLlvmString() << endl;
        }
        f->close();
    }

    void dumpMips(ofstream* f) {
        if (!GLOBALSTRINGS.empty()) {
            *f << ".data" << endl;
            for (auto i : GLOBALSTRINGS) *f << "\t" + i->toMipsString() << endl;
        }
        *f << ".text" << endl;
        *f << "\tj " + mainFunction->getEntry()->getLabel() + "\n";
        for (auto i : functions) {
            *f << i.second->toMipsString();
        }
        *f << mainFunction->toMipsString();
        *f << "\tli $v0, 10\n\tsyscall" << endl;
        f->close();
    }

    Function* getFunction(const string& ident) {
        return functions.at(ident);
    }

    map<string, Function*> getFunctions() {
        return functions;
    }

    Function* getMainFunction() {
        return mainFunction;
    }

    void setMainFunction(Function* func) {
        YASSERT(mainFunction == nullptr)
        mainFunction = func;
    }

private:
    SymbolTable symbolTable = SymbolTable(nullptr);
    map<string, Function*> functions;
    Function* mainFunction = nullptr;
};
#endif //TAYILER_MANAGER_H
