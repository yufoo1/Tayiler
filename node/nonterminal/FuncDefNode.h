//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCDEFNODE_H
#define TAYILER_FUNCDEFNODE_H

#include "../Node.h"

class FuncDefNode: public Node{
private:
    Node* funcType = nullptr;
    string* ident = nullptr;
    Node* funcFParams = nullptr;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCDEF, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::FUNCDEF;
    }

    void insertNode(Node* node) override {
        switch (node->getType()) {
            case SyntaxType::FUNCTYPE: assert(funcType == nullptr), funcType = node; break;
            case SyntaxType::IDENFR: assert(ident == nullptr), *ident = node->getVal(); break;
            case SyntaxType::FUNCFPARAMS: assert(funcFParams == nullptr), funcFParams = node; break;
            default: break;
        }
    }

    Node* getFuncType() {
        return funcType;
    }

    string* getIdent() {
        return ident;
    }

    Node* getFunFParams() {
        return funcFParams;
    }
};
#endif //TAYILER_FUNCDEFNODE_H
