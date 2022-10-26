//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_SEMICNNODE_H
#define TAYILER_SEMICNNODE_H

#include "../Node.h"

class SemicnNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::SEMICN, TokenMap.at(SyntaxType::SEMICN));
    }

    SyntaxType getType() override {
        return SyntaxType::SEMICN;
    }
};
#endif //TAYILER_SEMICNNODE_H
