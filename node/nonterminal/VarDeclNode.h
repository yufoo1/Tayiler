//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_VARDECLNODE_H
#define TAYILER_VARDECLNODE_H

#include "../Node.h"

class VarDeclNode: public Node {
private:
    Node* bType = nullptr;
public:
    vector<Node*> varDefs;
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::VARDECL, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::VARDECL;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::BTYPE: assert(bType == nullptr), bType = node; break;
            case SyntaxType::VARDEF: varDefs.emplace_back(node); break;
            default: break;
        }
    }

    BTypeNode* getBType() {
        return dynamic_cast<BTypeNode *>(bType);
    }

    vector<Node*> getVarDefs() {
        return varDefs;
    }
};
#endif //TAYILER_VARDECLNODE_H
