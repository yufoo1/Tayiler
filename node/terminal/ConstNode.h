//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_CONSTNODE_H
#define TAYILER_CONSTNODE_H

#include "../Node.h"

class ConstNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONSTTK, "const");
    }

    SyntaxType getType() override {
        return SyntaxType::CONSTTK;
    }
};
#endif //TAYILER_CONSTNODE_H
