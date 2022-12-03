//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LOREXPNODE_H
#define TAYILER_LOREXPNODE_H

#include "../Node.h"

class LOrExpNode: public Node {
private:
    vector<Node*> lAndExps;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LOREXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::LOREXP;
    }

    void insertNode(Node* node) override {
        if (node->getType() == SyntaxType::LANDEXP) {
            lAndExps.emplace_back(node);
        }
    }

    vector<Node*> getLAndExps() {
        return lAndExps;
    }
};
#endif //TAYILER_LOREXPNODE_H
