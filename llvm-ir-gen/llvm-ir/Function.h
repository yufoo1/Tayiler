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
class Param {
private:
    FuncType type;
    string ident;
    string val;
public:
    explicit Param(string ident, FuncType type) {
        this->ident = ident;
        this->type = type;
    }

    string getTypeString() {
        return FuncType2String.at(type);
    }

    void setVal(string val) {
        this->val = val;
    }

    string getVal() {
        return val;
    }

    FuncType getType() {
        return type;
    }

    string getIdent() {
        return ident;
    }
};

class Function: public Value {
private:
    string ident;
    vector<Param*>* params = nullptr;
    FuncType retType;
    BasicBlock* entry = nullptr;
    list<BasicBlock*> basicBlocks;
    BasicBlock* retBasicBlock = nullptr;
    int localInstrCnt;
public:
    explicit Function(string ident, vector<Param*>* params, FuncType retType) {
        this->ident = move(ident);
        this->params = params;
        this->retType = retType;
        this->localInstrCnt = 0;
    }

    explicit Function(string ident, FuncType retType) {
        this->ident = move(ident);
        this->retType = retType;
    }

    string getIdent() {
        return ident;
    }

    int genInstrIdx() {
        return localInstrCnt++;
    }

    vector<Param*>* getParams() {
        return params;
    }

    FuncType getRetType() {
        return retType;
    }

    void setBody(BasicBlock* entry) {
        this->entry = entry;
    }

    BasicBlock* getEntry() {
        return entry;
    }

    void addBasicBlock(BasicBlock* basicBlock) {
        basicBlocks.emplace_back(basicBlock);
    }

    bool hasEntry() {
        return entry != nullptr;
    }

    string getValueString() override {
        string s = "define dso_local ";
        s += FuncType2String.at(retType) + " @" + getIdent() + "(";
        if (params != nullptr) {
            for (int i = 0; i < params->size(); i++) {
                if (i != 0) s += ", ";
                s += params->at(i)->getTypeString() + " " + params->at(i)->getVal();
            }
        }
        s +=") {\n";
        for (auto i : basicBlocks) {
            s += i->getLabel() + ":\n";
            for (auto j : i->getInstrs()) {
                string str = j->toString();
               if (!str.empty()) s += "\t" + j->toString() + "\n";
            }
        }
        s += "}\n";
        return s;
    }
};
#endif //TAYILER_FUNCTION_H
