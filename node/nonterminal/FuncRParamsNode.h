//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCRPARAMSNODE_H
#define TAYILER_FUNCRPARAMSNODE_H

#include "../Node.h"

class FuncRParamsNode: public Node {
private:
    vector<Node*> exps;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCRPARAMS, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::FUNCFPARAMS;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::EXP: exps.emplace_back(node); break;
            default: break;
        }
    }

    vector<Node*> getExps() {
        return exps;
    }
};
#endif //TAYILER_FUNCRPARAMSNODE_H
