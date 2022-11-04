//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONSTEXPNODE_H
#define TAYILER_CONSTEXPNODE_H

#include "../Node.h"

class ConstExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONSTEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::CONSTEXP;
    }

    void insertNode(Node* node) override {
        YASSERT(child == nullptr)
        child = node;
    }
};
#endif //TAYILER_CONSTEXPNODE_H
