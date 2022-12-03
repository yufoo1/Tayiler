//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LANDEXPNODE_H
#define TAYILER_LANDEXPNODE_H

#include "../Node.h"

class LAndExpNode: public Node {
private:
    vector<Node*> eqExps;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LANDEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::LANDEXP;
    }

    void insertNode(Node* node) override {
        if (node->getType() == SyntaxType::EQEXP) {
            eqExps.emplace_back(node);
        }
    }

    vector<Node*> getEqExps() {
        return eqExps;
    }
};
#endif //TAYILER_LANDEXPNODE_H
