//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_BREAKSTMTNODE_H
#define TAYILER_BREAKSTMTNODE_H

#include "../Node.h"

class BreakNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::BREAKTK, "break");
    }

    SyntaxType getType() override {
        return SyntaxType::BREAKTK;
    }
};
#endif //TAYILER_BREAKSTMTNODE_H
