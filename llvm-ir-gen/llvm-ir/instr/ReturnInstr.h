//
// Created by yufoo1 on 2022/10/28.
//

#ifndef TAYILER_RETURNINSTR_H
#define TAYILER_RETURNINSTR_H

#include "Instr.h"

class ReturnInstr: public Instr {
private:
    Use* retUse = nullptr;
public:
    explicit ReturnInstr(BasicBlock* parent, Value* retValue) {
        retUse = new Use(retValue);
        parent->addInstr(this);
        this->setValueType(ValueType::RETURNINSTR);
    }

    explicit ReturnInstr(BasicBlock* parent) {
        parent->addInstr(this);
        this->setValueType(ValueType::RETURNINSTR);
    }

    std::string toString() override {
        if (hasValue()) {
            return "ret " + retUse->getValue()->getVal();
        } else {
            return "ret void";
        }
    }

    bool hasValue() override {
        return retUse != nullptr;
    }
};
#endif //TAYILER_RETURNINSTR_H
