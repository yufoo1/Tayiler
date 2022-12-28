//
// Created by yufoo1 on 2022/12/28.
//

#ifndef TAYILER_FORNODE_H
#define TAYILER_FORNODE_H
#include "../Node.h"

class ForNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FORTK, "for");
    }

    SyntaxType getType() override {
        return SyntaxType::FORTK;
    }
};
#endif //TAYILER_FORNODE_H
