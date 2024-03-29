//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_BTYPENODE_H
#define TAYILER_BTYPENODE_H

#include "../Node.h"

class BTypeNode: public Node {
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
//        parserList->emplace_back(SyntaxType::BTYPE, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::BTYPE;
    }

    void insertNode(Node* node) override {
        YASSERT(child == nullptr)
        child = node;
    }
};
#endif //TAYILER_BTYPENODE_H
