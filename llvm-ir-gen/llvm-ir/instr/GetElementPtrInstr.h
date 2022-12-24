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
    vector<int> nums;
    Use* baseUse = nullptr;
    Use* offsetUse = nullptr;
public:
    explicit GetElementPtrInstr(BasicBlock* parent, GlobalString* globalString, int idx) {
        genInstrVirtualReg(idx);
        setIsGetElementPtrInstr(true);
        this->setFuncType(FuncType::INT8);
        this->globalString = globalString;
        parent->addInstr(this);
    }

    explicit GetElementPtrInstr(BasicBlock* parent, Value* baseValue, Value* offsetValue, vector<int> nums, int idx) {
        genInstrVirtualReg(idx);
        setSize(4);
        setIsGetElementPtrInstr(true);
        this->baseUse = new Use(baseValue);
        this->offsetUse = new Use(offsetValue);
        this->setFuncType(FuncType::INT32);
        this->nums = nums;
        parent->addInstr(this);
    }

    explicit GetElementPtrInstr(BasicBlock* parent, Value* baseValue, Value* offsetValue, int idx) {
        genInstrVirtualReg(idx);
        setSize(4);
        setIsGetElementPtrInstr(true);
        this->baseUse = new Use(baseValue);
        this->offsetUse = new Use(offsetValue);
        this->setFuncType(FuncType::INT32);
        parent->addInstr(this);
    }

    string toLlvmString() {
        if(globalString != nullptr) {
            return getVal() + " = getelementptr inbounds " + "[" + to_string(globalString->getStr().length()) + " x " + FuncType2String.at(globalString->getFuncType()) + "], " + "[" +
                   to_string(globalString->getStr().length()) + " x " + FuncType2String.at(globalString->getFuncType()) + "]* " + globalString->getPrefix() + globalString->getLabel() + ", i32 0, i32 0";
        } else {
            string s;
            s += getVal() + " = getelementptr ";
            if(!nums.empty()) {
                for(auto i : nums) {
                    s += "[" + to_string(i) + " x ";
                }
                s += FuncType2String.at(getFuncType());
                for(auto i : nums) {
                    s += "]";
                }
                s += ", ";
                for(auto i : nums) {
                    s += "[" + to_string(i) + " x ";
                }
                s += FuncType2String.at(getFuncType());
                for(auto i : nums) {
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
            string s;
            s += "# >>> getElementPtrInstr\n";
            if (offsetUse->getValue()->isInstr()) {
                int offsetPos = GETPOS(ident, offsetUse->getValue());
                if(POSMAPHASPOS(ident, offsetUse->getValue())) {
                    s += "\tlw $t1, " + to_string(offsetPos) + "($t7)\n";
                } else {
                    s += "\tlw $t1, " + to_string(offsetPos) + "($sp)\n";
                }
            } else {
                s += "\tori $t1, $0, " + offsetUse->getValue()->getVal() + "\n";
            }
            s += "\tsll $t1, $t1, 2\n";
            if(POSMAPHASPOS(ident, baseUse->getValue())) {
                if(baseUse->getValue()->getIsGetElementPtrInstr()) {
                    s += "\tlw $t0, " + to_string(GETPOS(ident, baseUse->getValue())) + "($t7)\n";
                } else {
                    s += "\taddi $t0, $t7, " + to_string(GETPOS(ident, baseUse->getValue())) + "\n";
                }
            } else {
                if(baseUse->getValue()->getIsGetElementPtrInstr()) {
                    s += "\tlw $t0, " + to_string(GETPOS(ident, baseUse->getValue())) + "($sp)\n";
                } else {
                    s += "\taddi $t0, $sp, " + to_string(GETPOS(ident, baseUse->getValue())) + "\n";
                }
            }
            s += "\tadd $t0, $t0, $t1\n";
            int rdPos = GETPOS(ident, this);
            if(POSMAPHASPOS(ident, this)) {
                s += "\tsw $t0, " + to_string(rdPos) + "($t7)\n";
            } else {
                s += "\tsw $t0, " + to_string(rdPos) + "($sp)\n";
            }
            s += "# <<< getElementPtrInstr\n";
            return s;
        }
    }
};
#endif //TAYILER_GETELEMENTPTRINSTR_H
