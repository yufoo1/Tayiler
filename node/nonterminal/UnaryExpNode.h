//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_UNARYEXPNODE_H
#define TAYILER_UNARYEXPNODE_H

#include "../Node.h"

class UnaryExpNode: public Node {
private:
    Node* primaryExp = nullptr;
    string* ident = nullptr;
    Node* funcRParams = nullptr;

public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::UNARYEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::UNARYEXP;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::PRIMARYEXP: assert(ident == nullptr && funcRParams == nullptr), primaryExp = node; break;
            case SyntaxType::IDENFR: assert(primaryExp == nullptr), *ident = node->getVal(); break;
            case SyntaxType::FUNCRPARAMS: assert(primaryExp == nullptr), funcRParams = node; break;
            default: break;
        }
    }

    Node* getPrimaryExp() {
        return primaryExp;
    }

    string* getIdent() {
        return ident;
    }

    Node* getFuuncRParams() {
        return funcRParams;
    }
};
#endif //TAYILER_UNARYEXPNODE_H
