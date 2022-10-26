//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_STRCONNODE_H
#define TAYILER_STRCONNODE_H

#include "../Node.h"

class StrConNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList, string val) override {
        parserList->emplace_back(SyntaxType::STRCON, val);
    }
};
#endif //TAYILER_STRCONNODE_H
