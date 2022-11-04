//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_BLOCKITEMNODE_H
#define TAYILER_BLOCKITEMNODE_H

#include "../Node.h"

class BlockItemNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
//        parserList->emplace_back(SyntaxType::BLOCKITEM, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::BLOCKITEM;
    }

    void insertNode(Node* node) override {
        YASSERT(child == nullptr)
        child = node;
    }
};
#endif //TAYILER_BLOCKITEMNODE_H
