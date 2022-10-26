//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCTYPENODE_H
#define TAYILER_FUNCTYPENODE_H

#include "../Node.h"

class FuncTypeNode: public Node {
private:
    SyntaxType tokenType = SyntaxType::NONE;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCTYPE, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::FUNCTYPE;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::INTTK: assert(tokenType == SyntaxType::NONE), tokenType = SyntaxType::INTTK; break;
            case SyntaxType::VOIDTK: assert(tokenType == SyntaxType::NONE), tokenType = SyntaxType::VOIDTK; break;
            default: break;
        }
    }

    SyntaxType getTokenType() {
        return tokenType;
    }
};
#endif //TAYILER_FUNCTYPENODE_H
