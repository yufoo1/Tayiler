//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_PARSECURSOR_H
#define TAYILER_PARSECURSOR_H

#include <utility>
#include <vector>
#include "tuple"
#include "../lexer/SyntaxType.h"

using namespace std;
class ParseCursor {
private:
    int curIndex;
    vector<tuple<SyntaxType, string>> lexerList;
public:
    explicit ParseCursor(vector<tuple<SyntaxType, string>> lexerList) {
        curIndex = 0;
        this->lexerList = move(lexerList);
    }

    void next() {
        curIndex ++;
    }

    tuple<SyntaxType, string> getNthNode(int n) {
        return lexerList.at(curIndex + n);
    }

    bool judgeEnd() {
        return curIndex >= lexerList.size();
    }
};
#endif //TAYILER_PARSECURSOR_H
