//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_BASICBLOCK_H
#define TAYILER_BASICBLOCK_H

#include "Function.h"
#include "list"

static int BASICBLOCKCNT = 0;
static int EMPTYBASICBLOCKCNT = 0;

class Function;
class Instr;

class BasicBlock: public Value {
private:
    string label;
    Function* function = nullptr;
    vector<Instr*> instrs;
public:
    BasicBlock() {
        label = "EMPYT_BB" + to_string(++EMPTYBASICBLOCKCNT);
    }

    void setFunction(Function* function) {
        this->label = "b" + to_string((++BASICBLOCKCNT));
        this->function = function;
    }

    vector<Instr*> getInstrs() {
        return instrs;
    }

    void addInstr(Instr* instr) {
        instrs.emplace_back(instr);
    }

    string getLabel() {
        return label;
    }
};
#endif //TAYILER_BASICBLOCK_H
