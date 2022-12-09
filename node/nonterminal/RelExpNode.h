//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_RELEXPNODE_H
#define TAYILER_RELEXPNODE_H

#include "../Node.h"

class RelExpNode: public Node {
private:
    vector<SyntaxType> ops;
    vector<Node*> addExps;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::RELEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::RELEXP;
    }

    void insertNode(Node* node) override {
        set<SyntaxType> OP = {SyntaxType::LSS, SyntaxType::GRE, SyntaxType::LEQ, SyntaxType::GEQ};
        if (OP.count(node->getType())) {
            ops.emplace_back(node->getType());
        } else if (node->getType() == SyntaxType::ADDEXP) {
            addExps.emplace_back(node);
        }
    }

    vector<SyntaxType> getOps() {
        return ops;
    }

    vector<Node*> getAddExps() {
        return addExps;
    }
};
#endif //TAYILER_RELEXPNODE_H
