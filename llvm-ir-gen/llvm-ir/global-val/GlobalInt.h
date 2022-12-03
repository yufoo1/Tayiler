//
// Created by yufoo1 on 2022/10/31.
//

#ifndef TAYILER_GLOBALINT_H
#define TAYILER_GLOBALINT_H
#include "GlobalVal.h"
#include "../../../lexer/SyntaxType.h"
#include "../Use.h"

using namespace std;
class GlobalInt;
static std::set<GlobalInt*> GLOBALINTS;
class GlobalInt: public GlobalVal {
private:
    Use* allocaUse = nullptr;
public:
    explicit GlobalInt(Value* allocaInstr) {
        allocaUse = new Use(allocaInstr);
    }

    Use* getAllocaUse() {
        return allocaUse;
    }

    string toLlvmString() override { return ""; }

    string toMipsString() override {
        ALLOCSTACK(allocaUse->getValue());
        return "";
    }
};
#endif //TAYILER_GLOBALINT_H
