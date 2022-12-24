//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_GETINTINSTR_H
#define TAYILER_GETINTINSTR_H

#include "../Use.h"
#include "../../../lexer/SyntaxType.h"
#include "../BasicBlock.h"

class GetintInstr: public Instr {
public:
    explicit GetintInstr(BasicBlock* parent) {
        setSize(4);
        this->setFuncType(FuncType::INT32);
        parent->addInstr(this);
    }

    string toLlvmString() override {
        return "call " + FuncType2String.at(getFuncType()) + " @getint()";
    }

    string toMipsString_stack(string ident) override {
        string s;
        s += "# >>> getint\n";
        s += "\tli $v0, 5\n";
        s += "\tsyscall\n";
        int tarPos = GETPOS(ident, this);
        if(POSMAPHASPOS(ident, this)) {
            s += "\tsw $v0, " + to_string(tarPos) + "($t7)\n";
        } else {
            s += "\tsw $v0, " + to_string(tarPos) + "($sp)\n";
        }
        s += "# <<< getint\n";
        return s;
    }
};
#endif //TAYILER_GETINTINSTR_H
