//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCFPARAMSNODE_H
#define TAYILER_FUNCFPARAMSNODE_H

#include "../Node.h"

class FuncFParamsNode: public Node {
private:
    vector<Node*> funcFParams;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCFPARAMS, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::FUNCFPARAMS;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::FUNCFPARAM: funcFParams.emplace_back(node); break;
            default: break;
        }
    }

    vector<Node*> getFuncFParams() {
        return funcFParams;
    }
};
#endif //TAYILER_FUNCFPARAMSNODE_H
