//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_GLOBALVAL_H
#define TAYILER_GLOBALVAL_H

#include "../Value.h"
using namespace std;
class GlobalVal: public Value {
private:
    string prefix = "@";
public:
    explicit GlobalVal() = default;

    string getPrefix() {
        return prefix;
    }

    bool isInstr() override {
        return true;
    }
};
#endif //TAYILER_GLOBALVAL_H
