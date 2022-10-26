//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONDNODE_H
#define TAYILER_CONDNODE_H

#include "../Node.h"

class CondNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::COND, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_CONDNODE_H
