//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_GETINTNODE_H
#define TAYILER_GETINTNODE_H

#include "../Node.h"

class GetintNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::GETINTTK, "getint");
    }

    SyntaxType getType() override {
        return SyntaxType::GETINTTK;
    }
};
#endif //TAYILER_GETINTNODE_H
