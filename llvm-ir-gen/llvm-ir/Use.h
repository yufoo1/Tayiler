//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_USE_H
#define TAYILER_USE_H

#include "instr/Instr.h"
#include "Value.h"
static int indexCnt = 0;

class Use {
private:
    Value* value = nullptr;
    int index;
public:
    explicit Use(Value* used) {
        this->value = used;
        this->index = indexCnt++;
    }

    Value* getValue() {
        return value;
    }

    int getIndex() const {
        return index;
    }
};
#endif //TAYILER_USE_H
