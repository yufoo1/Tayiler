//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_MULEXPNODE_H
#define TAYILER_MULEXPNODE_H

#include "../Node.h"

class MulExpNode: public Node {
private:
    vector<SyntaxType> ops;
    vector<Node*> unaryExps;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::MULEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::MULEXP;
    }

    void insertNode(Node* node) override {
        set<SyntaxType> OP = {SyntaxType::MULT, SyntaxType::DIV, SyntaxType::MOD};
        if (OP.count(node->getType())) {
            ops.emplace_back(node->getType());
        } else if (node->getType() == SyntaxType::UNARYEXP) {
            unaryExps.emplace_back(node);
        }
    }

    vector<SyntaxType> getOps() {
        return ops;
    }

    vector<Node*> getUnaryExps() {
        return unaryExps;
    }
};
#endif //TAYILER_NODE_H
