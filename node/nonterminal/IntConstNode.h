//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_INTCONSTNODE_H
#define TAYILER_INTCONSTNODE_H

#include "../Node.h"

class IntConstNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::INTCONST, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_INTCONSTNODE_H
