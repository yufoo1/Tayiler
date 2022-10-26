//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_RETURNNODE_H
#define TAYILER_RETURNNODE_H

#include "../Node.h"

class ReturnNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::RETURNTK, "return");
    }

    SyntaxType getType() override {
        return SyntaxType::RETURNTK;
    }
};
#endif //TAYILER_RETURNNODE_H
