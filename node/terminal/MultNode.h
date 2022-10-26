//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_MULTNODE_H
#define TAYILER_MULTNODE_H

#include "../Node.h"

class MultNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::MULT, TokenMap.at(SyntaxType::MULT));
    }
};
#endif //TAYILER_MULTNODE_H
