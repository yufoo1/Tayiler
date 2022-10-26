//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_NEQNODE_H
#define TAYILER_NEQNODE_H

#include "../Node.h"

class NeqNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::NEQ, TokenMap.at(SyntaxType::NEQ));
    }

    SyntaxType getType() override {
        return SyntaxType::NEQ;
    }
};
#endif //TAYILER_NEQNODE_H
