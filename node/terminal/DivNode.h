//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_DIVNODE_H
#define TAYILER_DIVNODE_H

#include "../Node.h"

class DivNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::DIV, TokenMap.at(SyntaxType::DIV));
    }

    SyntaxType getType() override {
        return SyntaxType::DIV;
    }
};
#endif //TAYILER_DIVNODE_H
