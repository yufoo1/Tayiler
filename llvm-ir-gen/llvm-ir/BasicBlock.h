//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_BASICBLOCK_H
#define TAYILER_BASICBLOCK_H

#include "Function.h"
#include "Instr.h"

static int basicBlockCnt = 0;
static int emptyBasicBlockCnt = 0;

class Function;

class BasicBlock: public Value {
private:
    string label;
    Function* function;
    vector<Instr*> instrs;
    Instr* begin;
    Instr* end;
public:
    BasicBlock() {
        begin = new Instr, end = new Instr;
        label = "EMPYT_BB" + to_string(++emptyBasicBlockCnt);
        begin->setNext(end), end->setPrev(end);
    }

    void setFunction(Function* function) {
        this->label = "b" + to_string((++basicBlockCnt));
        this->function = function;
        // TODO function.insertAtBegin(this);
    }

    vector<Instr*> getInstrs() {
        return instrs;
    }

    string getOutputString() {
        return "";
    }
};
#endif //TAYILER_BASICBLOCK_H
