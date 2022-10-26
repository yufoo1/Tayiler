//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_BLOCKNODE_H
#define TAYILER_BLOCKNODE_H

#include "../Node.h"

class BlockNode: public Node {
private:
    vector<Node*> blockItems;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::BLOCK, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::BLOCK;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::BLOCKITEM: blockItems.emplace_back(node); break;
            default: break;
        }
    }

    vector<Node*> getBlockItems() {
        return blockItems;
    }
};
#endif //TAYILER_BLOCKNODE_H
