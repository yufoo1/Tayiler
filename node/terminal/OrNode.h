//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_ORNODE_H
#define TAYILER_ORNODE_H

#include "../Node.h"

class OrNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::OR, TokenMap.at(SyntaxType::OR));
    }
};
#endif //TAYILER_ORNODE_H
