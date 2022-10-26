//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_MODNODE_H
#define TAYILER_MODNODE_H

#include "../Node.h"

class ModNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::MOD, TokenMap.at(SyntaxType::MOD));
    }
};
#endif //TAYILER_MODNODE_H
