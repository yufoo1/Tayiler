//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_MAINFUNCDEFNODE_H
#define TAYILER_MAINFUNCDEFNODE_H

#include "../Node.h"
#include "BlockNode.h"

class MainFuncDefNode: public Node {
private:
    Node* block = nullptr;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::MAINFUNCDEF, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::MAINFUNCDEF;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::BLOCK: assert(block == nullptr), block = node; break;
            default: break;
        }
    }

    BlockNode* getBlock() {
        return dynamic_cast<BlockNode *>(block);
    }
};
#endif //TAYILER_MAINFUNCDEFNODE_H
