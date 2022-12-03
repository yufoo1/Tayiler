//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_ICMPINSTR_H
#define TAYILER_ICMPINSTR_H

#include "Instr.h"
#include "../../../lexer/SyntaxType.h"
#include "set"
#include "../BasicBlock.h"

class IcmpInstr: public Instr {
private:
    set<SyntaxType> opSet = {SyntaxType::LSS, SyntaxType::LEQ, SyntaxType::GRE, SyntaxType::GEQ, SyntaxType::EQL, SyntaxType::NEQ};
    SyntaxType op = SyntaxType::NONE;
    Use* useSrc1 = nullptr;
    Use* useSrc2 = nullptr;
public:
   explicit IcmpInstr(BasicBlock* parent, Value* src1, Value* src2, SyntaxType op, int idx) {
       YASSERT(opSet.count(op))
       useSrc1 = new Use(src1);
       useSrc2 = new Use(src2);
       setFuncType(FuncType::INT1);
       this->op = op;
       genInstrVirtualReg(idx);
       parent->addInstr(this);
   }

    string getOpString() {
        switch (op) {
            case SyntaxType::LSS: return "slt";
            case SyntaxType::LEQ: return "sle";
            case SyntaxType::GRE: return "sgt";
            case SyntaxType::GEQ: return "sge";
            case SyntaxType::EQL: return "eq";
            case SyntaxType::NEQ: return "ne";
            default: return "ERROR";
        }
    }

    string toLlvmString() override {
        return getVal() + " = icmp " + getOpString() + " " + FuncType2String.at(useSrc1->getValue()->getFuncType()) + " " + useSrc1->getValue()->getVal() + ", " + useSrc2->getValue()->getVal();
    }

    string toMipsString() override {
       return "";
   }
};
#endif //TAYILER_ICMPINSTR_H
