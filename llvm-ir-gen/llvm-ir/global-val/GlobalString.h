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
    int len;
    FuncType type;
    string label;
    string str;
public:
    explicit GlobalString(string str, FuncType type) {
        genLabel();
        this->len = str.length();
        this->type = type;
        this->str = str;
        GLOBALSTRINGS.insert(this);
    }

    string getLabel() {
        return label;
    }

    string getLenString() {
        return to_string(len);
    }

    string getTypeString() {
        return FuncType2String.at(type);
    }

    void genLabel() {
        label = getPrefix() + "_str_" + to_string(GLOBALSTRINGS.size());
    }

    string getStr() {
        return str;
    }
};
#endif //TAYILER_GLOBALSTRING_H
