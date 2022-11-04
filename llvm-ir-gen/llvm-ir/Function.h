//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_FUNCTION_H
#define TAYILER_FUNCTION_H


#include "Value.h"
#include "instr/AluInstr.h"
#include "instr/ReturnInstr.h"
#include "BasicBlock.h"
#include "../../lexer/SyntaxType.h"

using namespace std;
class Param: public Value {
private:
    string ident;
public:
    explicit Param(string ident, FuncType type) {
        this->ident = ident;
        setFuncType(type);
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
    SymbolTable* symbolTable = nullptr;
    int localInstrCnt;
public:
    explicit Function(BasicBlock* entry, SymbolTable* symbolTable, string ident, vector<Param*>* params, FuncType retType) {
        this->symbolTable = symbolTable;
        this->ident = move(ident);
        this->params = params;
        this->retType = retType;
        this->localInstrCnt = 0;
        setBody(entry);
        addBasicBlock(entry);
        entry->setFunction(this);
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

    SymbolTable* getSymbolTable() {
        return symbolTable;
    }

    string toLlvmString() override {
        string s = "define dso_local ";
        s += FuncType2String.at(retType) + " @" + getIdent() + "(";
        if (params != nullptr) {
            for (int i = 0; i < params->size(); i++) {
                if (i != 0) s += ", ";
                s += FuncType2String.at(params->at(i)->getFuncType()) + " " + params->at(i)->getVal();
            }
        }
        s +=") {\n";
        for (auto i : basicBlocks) {
            s += i->getLabel() + ":\n";
            for (auto j : i->getInstrs()) {
                string str = j->toLlvmString();
                if (!str.empty()) s += "\t" + str + "\n";
            }
        }
        s += "}\n";
        return s;
    }

    string toMipsString() override {
        string s;
        for (auto i : basicBlocks) {
            s += i->getLabel() + ":\n";
            for (auto j : i->getInstrs()) {
                string str = j->toMipsString();
                s += str;
            }
        }
        return s;
    }
};
#endif //TAYILER_FUNCTION_H
