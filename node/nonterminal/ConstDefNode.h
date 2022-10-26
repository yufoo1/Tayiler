//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONSTDEFNODE_H
#define TAYILER_CONSTDEFNODE_H

#include "../Node.h"
#include "ConstInitValNode.h"

class ConstDefNode: public Node {
private:
    string* ident = nullptr;
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
            case SyntaxType::IDENFR: assert(ident == nullptr), *ident = node->getVal(); break;
            case SyntaxType::CONSTEXP: constExps.emplace_back(node); break;
            case SyntaxType::CONSTINITVAL: assert(constInitVal == nullptr), constInitVal = node;
            default: break;
        }
    }

    string* getIdent() {
        return ident;
    }

    vector<Node*> getConstExps() {
        return constExps;
    }

    ConstInitValNode* getConstInitVal() {
        return dynamic_cast<ConstInitValNode *>(constInitVal);
    }
};
#endif //TAYILER_CONSTDEFNODE_H
