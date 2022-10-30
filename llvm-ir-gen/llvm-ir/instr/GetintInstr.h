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
    Use* use;
public:
    explicit GetintInstr(BasicBlock* parent, Value* val) {
        this->use = new Use(val);
        this->setFuncType(FuncType::INT32);
        parent->addInstr(this);
    }

    string toString() override {
        return "call " + getFuncTypeString() + " @getint" + "(" +
               FuncType2String.at(use->getValue()->getFuncType()) + " " + use->getValue()->getVal() + ")";
    }
};
#endif //TAYILER_GETINTINSTR_H
