//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_UNARYOPNODE_H
#define TAYILER_UNARYOPNODE_H

#include "../Node.h"

class UnaryOpNode: public Node {
private:
    SyntaxType tokenType = SyntaxType::NONE;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::UNARYOP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::UNARYOP;
    }

    void insertNode(Node *node) override {
        set<SyntaxType> set = {SyntaxType::PLUS, SyntaxType::MINU, SyntaxType::NOT};
        if (set.count(node->getType())) {
            assert(tokenType == SyntaxType::NONE);
            tokenType = node->getType();
        }
    }

    SyntaxType getTokenType() {
        return tokenType;
    }
};
#endif //TAYILER_UNARYOPNODE_H
