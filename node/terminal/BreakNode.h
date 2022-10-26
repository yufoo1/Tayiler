//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_BREAKNODE_H
#define TAYILER_BREAKNODE_H

#include "../Node.h"

class BreakNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::BREAKTK, "break");
    }
};
#endif //TAYILER_BREAKNODE_H
