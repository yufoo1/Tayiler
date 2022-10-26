//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_EQLNODE_H
#define TAYILER_EQLNODE_H

#include "../Node.h"

class EqlNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::EQL, TokenMap.at(SyntaxType::EQL));
    }
};
#endif //TAYILER_EQLNODE_H
