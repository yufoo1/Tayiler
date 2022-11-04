//
// Created by yufoo1 on 2022/10/28.
//

#ifndef TAYILER_RETURNINSTR_H
#define TAYILER_RETURNINSTR_H

#include "Instr.h"

class ReturnInstr: public Instr {
private:
    bool isMain;
    Use* retAllocaUse = nullptr;
    Use* retUse = nullptr;
public:
    explicit ReturnInstr(BasicBlock* parent, Value* retValue, Value* retAllocaValue, bool isMain) {
        if (retValue != nullptr) retUse = new Use(retValue);
        if (retAllocaValue != nullptr) retAllocaUse = new Use(retAllocaValue);
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

    string toMipsString() override {
        string s;
        if (!isMain) {
            if (retUse != nullptr) {
                if (retUse->getValue()->isInstr()) {
                    int retPos = STACKPOSMAP.at(retUse->getValue());
                    s += "\tlw $t0, " + to_string(retPos) + "($sp)\n";
                } else {
                    s += "\tori $t0, $0, " + retUse->getValue()->getVal() + "\n";
                }
                int retAllocaPos = STACKPOSMAP.at(retAllocaUse->getValue());
                s += "\tsw $t0, " + to_string(retAllocaPos) + "($sp)\n";
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
