//
// Created by yufoo1 on 2022/10/29.
//

#ifndef TAYILER_ALUINSTR_H
#define TAYILER_ALUINSTR_H
#include "Instr.h"
#include "../BasicBlock.h"
#include "../../Visitor.h"
#include "../../../utils/handler.h"

class AluInstr: public Instr {
private:
    set<SyntaxType> opSet = {SyntaxType::PLUS, SyntaxType::MINU, SyntaxType::NOT, SyntaxType::MULT, SyntaxType::DIV, SyntaxType::MOD};
    SyntaxType op = SyntaxType::NONE;
    Use* useSrc1 = nullptr;
    Use* useSrc2 = nullptr;
public:
    explicit AluInstr(BasicBlock* parent, Value* src1, Value* src2, SyntaxType op, int idx) {
        YASSERT(opSet.count(op))
        useSrc1 = new Use(src1);
        useSrc2 = new Use(src2);
        setFuncType(FuncType::INT32);
        this->op = op;
        genInstrVirtualReg(idx);
        parent->addInstr(this);
    }

    string getOpString() {
        switch (op) {
            case SyntaxType::PLUS: return "add";
            case SyntaxType::MINU: return "sub";
            case SyntaxType::MULT: return "mul";
            case SyntaxType::DIV: return "sdiv";
            case SyntaxType::MOD: return "mod";
            default: return "ERROR";
        }
    }

    string toLlvmString() override {
        return getVal() + " = " + getOpString() + " " + FuncType2String.at(useSrc1->getValue()->getFuncType()) + " " + useSrc1->getValue()->getVal() + ", " + useSrc2->getValue()->getVal();
    }

    string toMipsString_stack(string ident) override {
        string s;
        if (useSrc1->getValue()->isInstr()) {
            int rsPos = GETPOS(ident, useSrc1->getValue());
            if(POSMAPHASPOS(ident, useSrc1->getValue())) {
                s += "\tlw $t0, " + to_string(rsPos) + "($t7)\n";
            } else {
                s += "\tlw $t0, " + to_string(rsPos) + "($sp)\n";
            }
        } else {
            s += "\tori $t0, $0, " + useSrc1->getValue()->getVal() + "\n";
        }
        if (useSrc2->getValue()->isInstr()) {
            int rtPos = GETPOS(ident, useSrc2->getValue());
            if(POSMAPHASPOS(ident, useSrc2->getValue())) {
                s += "\tlw $t1, " + to_string(rtPos) + "($t7)\n";
            } else {
                s += "\tlw $t1, " + to_string(rtPos) + "($sp)\n";
            }
        } else {
            s += "\tori $t1, $0, " + useSrc2->getValue()->getVal() + "\n";
        }
        switch (op) {
            case SyntaxType::PLUS: {
                s += "\tadd $t0, $t0, $t1\n";
                break;
            }
            case SyntaxType::MINU: {
                s += "\tsub $t0, $t0, $t1\n";
                break;
            }
            case SyntaxType::MULT: {
                s += "\tmult $t0, $t1\n";
                s += "\tmflo $t0\n";
                break;
            }
            case SyntaxType::DIV: {
                s += "\tdiv $t0, $t1\n";
                s += "\tmflo $t0\n";
                break;
            }
            case SyntaxType::MOD: {
                s += "\tdiv $t0, $t1\n";
                s += "\tmfhi $t0\n";
                break;
            }
            default: break;
        }
        int rdPos = GETPOS(ident, this);
        if(POSMAPHASPOS(ident, this)) {
            s += "\tsw $t0, " + to_string(rdPos) + "($t7)\n";
        } else {
            s += "\tsw $t0, " + to_string(rdPos) + "($sp)\n";
        }
        return s;
    }

    bool hasValue() override {
        return useSrc1 != nullptr || useSrc2 != nullptr;
    }
};
#endif //TAYILER_ALUINSTR_H
