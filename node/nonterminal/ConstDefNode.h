//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONSTDEFNODE_H
#define TAYILER_CONSTDEFNODE_H

#include "../Node.h"
#include "ConstInitValNode.h"
#include "../terminal/IdentNode.h"

class ConstDefNode: public Node {
private:
    Node* ident = nullptr;
    vector<Node*> constExps;
    Node* constInitVal = nullptr;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONSTDEF, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::CONSTDEF;
    }

    void insertNode(Node* node) override {
        switch (node->getType()) {
            case SyntaxType::IDENFR: YASSERT(ident == nullptr) ident = node; break;
            case SyntaxType::CONSTEXP: constExps.emplace_back(node); break;
            case SyntaxType::CONSTINITVAL: YASSERT(constInitVal == nullptr) constInitVal = node;
            default: break;
        }
    }

    IdentNode* getIdent() {
        return dynamic_cast<IdentNode *>(ident);
    }

    vector<Node*> getConstExps() {
        return constExps;
    }

    ConstInitValNode* getConstInitVal() {
        return dynamic_cast<ConstInitValNode *>(constInitVal);
    }
};
#endif //TAYILER_CONSTDEFNODE_H
