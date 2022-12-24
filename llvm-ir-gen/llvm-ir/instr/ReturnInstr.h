//
// Created by yufoo1 on 2022/10/28.
//

#ifndef TAYILER_RETURNINSTR_H
#define TAYILER_RETURNINSTR_H

#include "Instr.h"

class ReturnInstr: public Instr {
private:
    bool isMain;
    Use* retUse = nullptr;
public:
    explicit ReturnInstr(BasicBlock* parent, Value* retValue, bool isMain) {
        if (retValue != nullptr) retUse = new Use(retValue);
        this->isMain = isMain;
        parent->addInstr(this);
    }

    string toLlvmString() override {
        if (hasValue()) {
            return "ret " + retUse->getValue()->getVal();
        } else {
            return "ret void";
        }
    }

    string toMipsString_stack(string ident) override {
        string s;
        if (!isMain) {
            if (retUse != nullptr) {
                if (retUse->getValue()->isInstr()) {
                    int retPos = GETPOS(ident, retUse->getValue());
                    if(POSMAPHASPOS(ident, retUse->getValue())) {
                        s += "\tlw $v0, " + to_string(retPos) + "($gp)\n";
                    } else {
                        s += "\tlw $v0, " + to_string(retPos) + "($sp)\n";
                    }
                } else {
                    s += "\tori $v0, $0, " + retUse->getValue()->getVal() + "\n";
                }
            }
            s += "\tjr $ra\n";
        }
        return s;
    }

    bool hasValue() override {
        return retUse != nullptr;
    }
};
#endif //TAYILER_RETURNINSTR_H
