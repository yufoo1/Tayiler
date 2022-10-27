//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_FUNCTION_H
#define TAYILER_FUNCTION_H

#include <utility>

#include "Value.h"
#include "BasicBlock.h"
#include "../../lexer/SyntaxType.h"

using namespace std;

class Function: public Value {
public:
    class Param {

    };
private:
    string ident;
    vector<Function::Param>* params;
    FuncType retType;
    BasicBlock* entry = nullptr;
    vector<BasicBlock*> basicBlocks;
public:
    explicit Function(string ident, vector<Param> *params, FuncType retType) {
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

    vector<Function::Param>* getParams() {
        return params;
    }

    FuncType getRetType() {
        return retType;
    }

    void setBody(BasicBlock* entry) {
        this->entry = entry;
    }

    bool hasEntry() {
        return entry != nullptr;
    }

    string getOutputString() {
        string s = "define dso_local ";
        s += FuncType2String.at(retType) + " @" + getIdent() + "() {\n";
        for (auto i : basicBlocks) {
            s += i->getOutputString() + ":\n";
            for (auto j : i->getInstrs()) {
                s += "\t" + j->getOutputString() + "\n";
            }
        }
        s += "}\n";
        return s;
    }
};
#endif //TAYILER_FUNCTION_H
