//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONSTINITVALNODE_H
#define TAYILER_CONSTINITVALNODE_H

#include "../Node.h"
#include "ConstExpNode.h"

class ConstInitValNode: public Node {
private:
    Node* constExp = nullptr;
    vector<Node*> constInitVals;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONSTINITVAL, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::CONSTINITVAL;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::CONSTEXP: assert(constInitVals.empty()), constExp = node; break;
            case SyntaxType::CONSTINITVAL: assert(constExp == nullptr), constInitVals.emplace_back(node); break;
            default: break;
        }
    }

    ConstExpNode* getConstExp() {
        return dynamic_cast<ConstExpNode *>(constExp);
    }

    vector<Node*> getConstInitVals() {
        return constInitVals;
    }
};
#endif //TAYILER_CONSTINITVALNODE_H
