//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_NUMBERNODE_H
#define TAYILER_NUMBERNODE_H

#include "../Node.h"

class NumberNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::NUMBER, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::NUMBER;
    }

    void insertNode(Node* node) override {
        assert(child == nullptr);
        child = node;
    }
};
#endif //TAYILER_NUMBERNODE_H
