//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LVALNODE_H
#define TAYILER_LVALNODE_H

#include "../Node.h"

class LValNode: public Node {
private:
    Node* ident = nullptr;
    vector<Node*> exps;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LVAL, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::LVAL;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::IDENFR: YASSERT(ident == nullptr) ident = node; break;
            case SyntaxType::EXP: exps.emplace_back(node);
            default: break;
        }
    }

    IdentNode* getIdent() {
        return dynamic_cast<IdentNode *>(ident);
    }

    vector<Node*> getExps() {
        return exps;
    }
};
#endif //TAYILER_LVALNODE_H
