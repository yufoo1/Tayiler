//
// Created by yufoo1 on 2022/10/30.
//

#ifndef TAYILER_GLOBALSTRING_H
#define TAYILER_GLOBALSTRING_H

#include "GlobalVal.h"
#include "../../../lexer/SyntaxType.h"
using namespace std;
class GlobalString;
static std::set<GlobalString*> GLOBALSTRINGS;
class GlobalString: public GlobalVal {
private:
    string label;
    string str;
public:
    explicit GlobalString(const string& str) {
        genLabel();
        setFuncType(FuncType::INT8);
        this->str = str;
        GLOBALSTRINGS.insert(this);
    }

    string getLabel() {
        return label;
    }

    void genLabel() {
        label = getPrefix() + "_str_" + to_string(GLOBALSTRINGS.size());
    }

    string getStr() {
        return str;
    }

    string toString() override {
        return label + " = constant " + "[" + to_string(str.length()) + " x " + FuncType2String.at(getFuncType()) + "] c\"" + getStr() + "\"";
    }
};
#endif //TAYILER_GLOBALSTRING_H
