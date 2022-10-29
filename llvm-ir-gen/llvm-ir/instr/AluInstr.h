//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_ALUINSTR_H
#define TAYILER_ALUINSTR_H
#include "Instr.h"
#include "../constant/ConstantInt.h"

class AluInstr: public Instr {
private:
    set<SyntaxType> set = {SyntaxType::PLUS, SyntaxType::MINU, SyntaxType::NOT, SyntaxType::MULT, SyntaxType::DIV, SyntaxType::MOD};
    SyntaxType op = SyntaxType::NONE;
    Use* useSrc1 = nullptr;
    Use* useSrc2 = nullptr;
public:
    explicit AluInstr(BasicBlock* parent, Value* src1, Value* src2, SyntaxType op) {
        assert(set.count(op));
        useSrc1 = new Use(src1);
        useSrc2 = new Use(src2);
        this->op = op;
        setValueType(ValueType::ALUINSTR);
        setVal(LOCAL_PREFIX + LOCAL_NAME_PREFIX + to_string(LOCAL_INSTR_CNT++));
        parent->addInstr(this);
    }

    string getOpString() {
        switch (op) {
            case SyntaxType::PLUS: return "add";
            case SyntaxType::MINU: return "sub";
            case SyntaxType::MULT: return "mul";
            case SyntaxType::DIV: return "sdiv";
            case SyntaxType::MOD: return "mod";
            default: break;
        }
    }

    string toString() override {
        return getVal() + " = " + getOpString() + " " + useSrc1->getValue()->getFuncTypeString() + " " + useSrc1->getValue()->getVal() + ", " + useSrc2->getValue()->getVal();
    }

    bool hasValue() override {
        return useSrc1 != nullptr || useSrc2 != nullptr;
    }
};
#endif //TAYILER_ALUINSTR_H
