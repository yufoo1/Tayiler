//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_GRENODE_H
#define TAYILER_GRENODE_H

#include "../Node.h"

class GreNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::GRE, TokenMap.at(SyntaxType::GRE));
    }

    SyntaxType getType() override {
        return SyntaxType::GRE;
    }
};
#endif //TAYILER_GRENODE_H
