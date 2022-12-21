//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_GETELEMENTPTRINSTR_H
#define TAYILER_GETELEMENTPTRINSTR_H

#include "Instr.h"
#include "../global-val/GlobalString.h"
#include "../BasicBlock.h"

class GetElementPtrInstr: public Instr {
private:
    GlobalString* globalString = nullptr;
    vector<int>* nums = nullptr;
    Use* baseUse = nullptr;
    Use* offsetUse = nullptr;
public:
    explicit GetElementPtrInstr(BasicBlock* parent, GlobalString* globalString, int idx) {
        genInstrVirtualReg(idx);
        this->setFuncType(FuncType::INT8);
        this->globalString = globalString;
        parent->addInstr(this);
    }

    explicit GetElementPtrInstr(BasicBlock* parent, Value* baseValue, Value* offsetValue, vector<int>* nums, int idx) {
        genInstrVirtualReg(idx);
        this->baseUse = new Use(baseValue);
        this->offsetUse = new Use(offsetValue);
        this->setFuncType(FuncType::INT32);
        this->nums = nums;
        parent->addInstr(this);
    }

    string toLlvmString() {
        if(globalString != nullptr) {
            return getVal() + " = getelementptr inbounds " + "[" + to_string(globalString->getStr().length()) + " x " + FuncType2String.at(globalString->getFuncType()) + "], " + "[" +
                   to_string(globalString->getStr().length()) + " x " + FuncType2String.at(globalString->getFuncType()) + "]* " + globalString->getPrefix() + globalString->getLabel() + ", i32 0, i32 0";
        } else {
            string s;
            s += getVal() + " = getelementptr ";
            if(nums != nullptr) {
                for(auto i : *nums) {
                    s += "[" + to_string(i) + " x ";
                }
                s += FuncType2String.at(getFuncType());
                for(auto i : *nums) {
                    s += "]";
                }
                s += ", ";
                for(auto i : *nums) {
                    s += "[" + to_string(i) + " x ";
                }
                s += FuncType2String.at(getFuncType());
                for(auto i : *nums) {
                    s += "]";
                }
                s += "* " + baseUse->getValue()->getVal() + ", " + FuncType2String.at(getFuncType()) + " 0, " + FuncType2String.at(getFuncType()) + " 0";
            } else {
                s += FuncType2String.at(getFuncType()) + ", " + FuncType2String.at(getFuncType()) + "* " + baseUse->getValue()->getVal() + ", " + FuncType2String.at(getFuncType()) + " " + offsetUse->getValue()->getVal();
                return s;
            }
            return s;
        }
    }

    string toMipsString_stack(string ident) {
        if(globalString != nullptr) {
            return "\tla $a0, " + globalString->getLabel() + "\n";
        } else {
            return "";
        }
    }
};
#endif //TAYILER_GETELEMENTPTRINSTR_H
