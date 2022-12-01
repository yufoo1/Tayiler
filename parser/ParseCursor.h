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
    vector<tuple<SyntaxType, string, int>> lexerList;
public:
    explicit ParseCursor(vector<tuple<SyntaxType, string, int>> lexerList) {
        curIndex = 0;
        this->lexerList = move(lexerList);
    }

    void next() {
        curIndex ++;
    }

    tuple<SyntaxType, string, int> getNthNode(int n) {
        return lexerList.at(curIndex + n);
    }

    bool judgeEnd() {
        return curIndex >= lexerList.size();
    }

    bool judgeEnd(int n) {
        return curIndex + n >= lexerList.size();
    }
};
#endif //TAYILER_PARSECURSOR_H
