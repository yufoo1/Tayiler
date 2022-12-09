//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_MANAGER_H
#define TAYILER_MANAGER_H


#include "../llvm-ir-gen/symbol/SymbolTable.h"
#include "../llvm-ir-gen/llvm-ir/Function.h"
#include "../llvm-ir-gen/llvm-ir/global-val/GlobalString.h"
#include "../utils/handler.h"
#include "../llvm-ir-gen/llvm-ir/global-val/GlobalInt.h"

class Manager {
public:
    explicit Manager(vector<tuple<int, string>>* errorList) {
        this->errorList = errorList;
    }

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
//        if (!GLOBALINTS.empty()) {
//            for (auto i : GLOBALSTRINGS) *f << "\t" + i->toMipsString() << endl;
//        }
        *f << ".text" << endl;
        for (auto i : globalBasicBlock->getInstrs()) {
            *f << i->toMipsString();
        }
        *f << "\tj " + mainFunction->getEntry()->getLabel() + "\n";
        for (auto i : functions) {
            *f << i.second->toMipsString();
        }
        *f << "\tjr $ra\n";
        *f << mainFunction->toMipsString();
        f->close();
    }

    static bool compare(const tuple<int, string>& a, const tuple<int, string>& b) {
        return std::tie(get<0>(a), get<1>(a)) < std::tie(get<0>(b), get<1>(b));
    }

    void dumpError(ofstream* f) {
        std::sort(errorList->begin(), errorList->end(), compare);
        for(auto i : *errorList) {
            *f << to_string(get<0>(i)) + " " + get<1>(i) << endl;
        }
    }

    Function* getFunction(const string& ident) {
        return functions.at(ident);
    }

    bool hasFunction(const string& ident) {
        return functions.count(ident);
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

    void setGlobalBasicBlock(BasicBlock* basicBlock) {
        YASSERT(globalBasicBlock == nullptr)
        globalBasicBlock = basicBlock;
    }

private:
    SymbolTable symbolTable = SymbolTable(nullptr);
    map<string, Function*> functions;
    Function* mainFunction = nullptr;
    BasicBlock* globalBasicBlock = nullptr;
    vector<tuple<int, string>>* errorList = nullptr;
};
#endif //TAYILER_MANAGER_H
