//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_ALLOCAINSTR_H
#define TAYILER_ALLOCAINSTR_H

#include "Instr.h"

#include <utility>
#include "../../symbol/SymbolTable.h"
#include "../../symbol/SymbolTerm.h"
class AllocaInstr: public Instr {
private:
    string ident;
    bool isParam; /* when is param, no need to output this alloca instr. */
    SymbolTable* table;
    vector<int> nums;
public:
    explicit AllocaInstr(BasicBlock* parent, SymbolTable* table, string ident, FuncType type, bool isConstant, bool isParam, int idx) {
        genInstrVirtualReg(idx);
        setFuncType(type);
        this->table = table;
        this->isParam = isParam;
        this->ident = std::move(ident);
        setSize(4);
        if (parent != nullptr) parent->addInstr(this);
    }

    explicit AllocaInstr(BasicBlock* parent, SymbolTable* table, string ident, FuncType type, bool isConstant, bool isParam, int idx, vector<int> nums) {
        genInstrVirtualReg(idx);
        setFuncType(type);
        this->table = table;
        this->isParam = isParam;
        this->ident = std::move(ident);
        int size = 4;
        for(auto i : nums) size *= i;
        setSize(size);
        this->nums = nums;
        if (parent != nullptr) parent->addInstr(this);
    }

    void setNums(vector<int> nums) {
        for(int & num : nums) {
            this->nums.emplace_back(num);
        }
    }

    string getIdent() {
        return ident;
    }

    string toLlvmString() override {
        if(isParam) {
            return "";
        } else {
            if(table->getSymbolTerm(ident)->getDimensionality() == 0) {
                return getVal() + " = alloca " + FuncType2String.at(getFuncType());
            } else {
                string s;
                s += getVal() +" = alloca ";
                for(int i = 0; i < table->getSymbolTerm(ident)->getDimensionality(); ++i) {
                    s += "[" + to_string(nums.at(i)) + " x ";
                }
                s += FuncType2String.at(getFuncType());
                for(int i = 0; i < table->getSymbolTerm(ident)->getDimensionality(); ++i) {
                    s += "]";
                }
                return s;
            }
        }
    }

    string toMipsString_stack(string ident) override {
        return "";
    }

    vector<int> getNums() {
        return nums;
    }
};
#endif //TAYILER_ALLOCAINSTR_H
