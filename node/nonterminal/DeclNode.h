//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_DECLNODE_H
#define TAYILER_DECLNODE_H

#include "../Node.h"

class DeclNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
//        parserList->emplace_back(SyntaxType::DECL, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::DECL;
    }

    void insertNode(Node* node) override {
        YASSERT(child == nullptr)
        child = node;
    }
};
#endif //TAYILER_DECLNODE_H
