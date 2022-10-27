//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_USE_H
#define TAYILER_USE_H

#include "Instr.h"
#include "Value.h"

class Use {
private:
    Instr instr;
    Value used;
    int index;
public:
    explicit Use(Instr instr, Value used, int index) {
        this-> instr = instr;
        this->used = used;
        this->index = index;
    }

    Instr getInstr() {
        return instr;
    }

    Value getUsed() {
        return used;
    }

    int getIndex() {
        return index;
    }
};
#endif //TAYILER_USE_H
