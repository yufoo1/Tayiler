//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCFPARAMNODE_H
#define TAYILER_FUNCFPARAMNODE_H

#include "../Node.h"

class FuncFParamNode: public Node {
private:
    Node* bType = nullptr;
    Node* ident = nullptr;
    bool isArray = false;
    vector<Node*> constExps;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCFPARAM, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::FUNCFPARAM;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::BTYPE: YASSERT(bType == nullptr) bType = node; break;
            case SyntaxType::IDENFR: YASSERT(ident == nullptr) ident = node; break;
            case SyntaxType::LBRACK: isArray = true; break;
            case SyntaxType::CONSTEXP: YASSERT(isArray) constExps.emplace_back(node); break;
            default: break;
        }
    }

    BTypeNode* getBType() {
        return dynamic_cast<BTypeNode *>(bType);
    }

    IdentNode* getIdent() {
        return dynamic_cast<IdentNode *>(ident);
    }

    bool getIsArray() {
        return isArray;
    }

    vector<Node*> getConstExps() {
        return constExps;
    }
};
#endif //TAYILER_FUNCFPARAMNODE_H
