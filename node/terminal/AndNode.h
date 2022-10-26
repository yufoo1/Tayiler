//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_ANDNODE_H
#define TAYILER_ANDNODE_H

#include "../Node.h"

class AndNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::AND, TokenMap.at(SyntaxType::AND));
    }

    SyntaxType getType() override {
        return SyntaxType::AND;
    }
};
#endif //TAYILER_ANDNODE_H
