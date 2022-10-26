//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_ASSIGNNODE_H
#define TAYILER_ASSIGNNODE_H

#include "../Node.h"

class AssignNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::ASSIGN, TokenMap.at(SyntaxType::ASSIGN));
    }

    SyntaxType getType() override {
        return SyntaxType::ASSIGN;
    }
};
#endif //TAYILER_ASSIGNNODE_H
