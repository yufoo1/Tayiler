//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONSTDECLNODE_H
#define TAYILER_CONSTDECLNODE_H

#include "../Node.h"

class ConstDeclNode: public Node {
private:
    Node* bType = nullptr;
    vector<Node*> constDefs;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONSTDECL, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::CONSTDECL;
    }

    void insertNode(Node* node) override {
        switch (node->getType()) {
            case SyntaxType::BTYPE: assert(bType == nullptr), bType = node; break;
            case SyntaxType::FUNCDEF: constDefs.emplace_back(node); break;
            default: break;
        }
    }

    BTypeNode* getBType() {
        return dynamic_cast<BTypeNode *>(bType);
    }

    vector<Node*> getConstDefs() {
        return constDefs;
    }
};
#endif //TAYILER_CONSTDECLNODE_H
