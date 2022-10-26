//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_VARDEFNODE_H
#define TAYILER_VARDEFNODE_H

#include "../Node.h"

class VarDefNode: public Node {
private:
    string* ident = nullptr;
    vector<Node*> constExps;
    Node* constInitVal = nullptr;
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::VARDEF, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::VARDEF;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::IDENFR: assert(ident == nullptr), *ident = node->getVal(); break;
            case SyntaxType::CONSTEXP: constExps.emplace_back(node); break;
            case SyntaxType::CONSTINITVAL: assert(constInitVal == nullptr), constInitVal = node; break;
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
#endif //TAYILER_VARDEFNODE_H
