//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_INSTR_H
#define TAYILER_INSTR_H

#include "Value.h"
#include "BasicBlock.h"

class BasicBlock;

class Instr: public Value {
private:
    Value* next;
    Value* prev;
public:
    Instr() {

    }

    void setNext(Value* value) {
        this->next = value;
    }

    void setPrev(Value* value) {
        this->prev = value;
    }

    string getOutputString() {
        return "";
    }

    class AluInstr {

    };

    class ReturnInstr {

    public:
        explicit ReturnInstr(BasicBlock* parent, Value retValue) {

        }

        explicit ReturnInstr(BasicBlock* parent) {

        }
    };
};
#endif //TAYILER_INSTR_H
