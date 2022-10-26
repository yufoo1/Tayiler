//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_EQEXPNODE_H
#define TAYILER_EQEXPNODE_H

#include "../Node.h"

class EqExpNode: public Node {
private:
    vector<SyntaxType> ops;
    vector<Node*> relExps;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::EQEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::EQEXP;
    }

    void insertNode(Node* node) override {
        set<SyntaxType> OP = {SyntaxType::EQL, SyntaxType::NEQ};
        if (OP.count(node->getType())) {
            ops.emplace_back(node->getType());
        } else if (node->getType() == SyntaxType::RELEXP) {
            relExps.emplace_back(node);
        }
    }

    vector<SyntaxType> getOps() {
        return ops;
    }

    vector<Node*> getRelExps() {
        return relExps;
    }
};
#endif //TAYILER_EQEXPNODE_H
