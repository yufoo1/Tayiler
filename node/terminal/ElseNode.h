//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_ELSENODE_H
#define TAYILER_ELSENODE_H

#include "../Node.h"

class ElseNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::ELSETK, "else");
    }

    SyntaxType getType() override {
        return SyntaxType::ELSETK;
    }
};
#endif //TAYILER_ELSENODE_H
