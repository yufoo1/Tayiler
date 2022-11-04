//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_GETINTINSTR_H
#define TAYILER_GETINTINSTR_H

#include "../Use.h"
#include "../../../lexer/SyntaxType.h"
#include "../BasicBlock.h"

class GetintInstr: public Instr {
private:
    Use* tarUse = nullptr;
public:
    explicit GetintInstr(BasicBlock* parent, Value* val) {
        this->tarUse = new Use(val);
        this->setFuncType(FuncType::INT32);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return "call " + FuncType2String.at(getFuncType()) + " @getint" + "(" +
               FuncType2String.at(tarUse->getValue()->getFuncType()) + " " + tarUse->getValue()->getVal() + ")";
    }

    string toMipsString() override {
        string s;
        s += "\tli $v0, 5\n";
        s += "\tsyscall\n";
        int tarPos = STACKPOSMAP.at(tarUse->getValue());
        s += "\tsw $v0, " + to_string(tarPos) + "($sp)\n";
        return s;
    }
};
#endif //TAYILER_GETINTINSTR_H
