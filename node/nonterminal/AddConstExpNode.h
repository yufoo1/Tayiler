//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_ADDCONSTEXPNODE_H
#define TAYILER_ADDCONSTEXPNODE_H

#include "../Node.h"
#include "MulExpNode.h"

class AddConstExpNode: public Node {
private:
    vector<SyntaxType> ops;
    vector<Node*> mulExps;

public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(/* not typo */SyntaxType::ADDEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::ADDCONSTEXP;
    }

    void insertNode(Node* node) override {
        set<SyntaxType> OP = {SyntaxType::PLUS, SyntaxType::MINU};
        if (OP.count(node->getType())) {
            ops.emplace_back(node->getType());
        } else if (node->getType() == SyntaxType::MULEXP) {
            mulExps.emplace_back(node);
        }
    }

    vector<SyntaxType> getOps() {
        return ops;
    }

    vector<Node*> getMulExps() {
        return mulExps;
    }
};
#endif //TAYILER_ADDCONSTEXPNODE_H
