//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_FUNCTION_H
#define TAYILER_FUNCTION_H

#include <utility>

#include "Value.h"
#include "instr/AluInstr.h"
#include "instr/ReturnInstr.h"
#include "BasicBlock.h"
#include "../../lexer/SyntaxType.h"

using namespace std;

class Function: public Value {
public:
    class Param {

    };
private:
    string ident;
    list<Function::Param>* params;
    FuncType retType;
    BasicBlock* entry = nullptr;
    list<BasicBlock*> basicBlocks;
public:
    explicit Function(string ident, list<Param> *params, FuncType retType) {
        this->ident = move(ident);
        this->params = params;
        this->retType = retType;
    }

    explicit Function(string ident, FuncType retType) {
        this->ident = move(ident);
        this->retType = retType;
    }

    string getIdent() {
        return ident;
    }

    list<Function::Param>* getParams() {
        return params;
    }

    FuncType getRetType() {
        return retType;
    }

    void setBody(BasicBlock* entry) {
        this->entry = entry;
    }

    void addBasicBlock(BasicBlock* basicBlock) {
        basicBlocks.emplace_back(basicBlock);
    }

    bool hasEntry() {
        return entry != nullptr;
    }

    string getValueString() override {
        string s = "define dso_local ";
        s += FuncType2String.at(retType) + " @" + getIdent() + "() {\n";
        for (auto i : basicBlocks) {
            s += i->getLabel() + ":\n";
            for (auto j : i->getInstrs()) {
                string str;
                s += "\t" + j->toString() + "\n";
            }
        }
        s += "}\n";
        return s;
    }
};
#endif //TAYILER_FUNCTION_H
