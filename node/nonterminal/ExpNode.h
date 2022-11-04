//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_EXPNODE_H
#define TAYILER_EXPNODE_H

#include "../Node.h"

class ExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::EXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::EXP;
    }

    void insertNode(Node* node) override {
        YASSERT(child == nullptr)
        child = node;
    }
};
#endif //TAYILER_EXPNODE_H
