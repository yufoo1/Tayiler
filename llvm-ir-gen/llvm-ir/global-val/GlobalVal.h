//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_GLOBALVAL_H
#define TAYILER_GLOBALVAL_H

#include <string>
#include "../Value.h"
using namespace std;
class GlobalVal: public Value {
private:
    string prefix = "@";
public:
    explicit GlobalVal() { }
protected:
    string getPrefix() {
        return prefix;
    }
};
#endif //TAYILER_GLOBALVAL_H
