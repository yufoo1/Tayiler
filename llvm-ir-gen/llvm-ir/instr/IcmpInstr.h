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
        string s;
        if (useSrc1->getValue()->isInstr()) {
            int rsPos = STACKPOSMAP.at(useSrc1->getValue());
            s += "\tlw $t0, " + to_string(rsPos) + "($sp)\n";
        } else {
            s += "\tori $t0, $0, " + useSrc1->getValue()->getVal() + "\n";
        }
        if (useSrc2->getValue()->isInstr()) {
            int rtPos = STACKPOSMAP.at(useSrc2->getValue());
            s += "\tlw $t1, " + to_string(rtPos) + "($sp)\n";
        } else {
            s += "\tori $t1, $0, " + useSrc2->getValue()->getVal() + "\n";
        }
        ALLOCSTACK(this);
        int rdPos = STACKPOSMAP.at(this);
        switch (op) {
            case SyntaxType::LSS: {
                s += "\tslt $t0, $t0, $t1\n";
                break;
            }
            case SyntaxType::LEQ: {
                s += "\tslt $t0, $t1, $t0\n";
                s += "\tori $t1, $0, 1\n";
                s += "\txor $t0, $t0, $t1\n";
                break;
            }
            case SyntaxType::GRE: {
                s += "\tslt $t0, $t1, $t0\n";
                break;
            }
            case SyntaxType::GEQ: {
                s += "\tslt $t0, $t0, $t1\n";
                s += "\tori $t1, $0, 1\n";
                s += "\txor $t0, $t0, $t1\n";
                break;
            }
            case SyntaxType::EQL: {
                s += "\tslt $t2, $t0, $t1\n";
                s += "\tslt $t0, $t1, $t0\n";
                s += "\tnor $t0, $t0, $t2\n";
                s += "\tandi $t0, $t0, 1\n";
                break;
            }
            case SyntaxType::NEQ: {
                s += "\tslt $t2, $t0, $t1\n";
                s += "\tslt $t0, $t1, $t0\n";
                s += "\tor $t0, $t0, $t2\n";
                break;
            }
        }
        s += "\tsw $t0, " + to_string(rdPos) + "($sp)\n";
        return s;
   }
};
#endif //TAYILER_ICMPINSTR_H
