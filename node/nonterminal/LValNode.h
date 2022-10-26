//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LVALNODE_H
#define TAYILER_LVALNODE_H

#include "../Node.h"

class LValNode: public Node {
private:
    string* ident = nullptr;
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
            case SyntaxType::IDENFR: assert(ident == nullptr), *ident = node->getVal(); break;
            case SyntaxType::EXP: exps.emplace_back(node);
            default: break;
        }
    }

    string* getIdent() {
        return ident;
    }

    vector<Node*> getExps() {
        return exps;
    }
};
#endif //TAYILER_LVALNODE_H
