//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_IDENTNODE_H
#define TAYILER_IDENTNODE_H

#include "../Node.h"

class IdentNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList, string val) override {
        parserList->emplace_back(SyntaxType::IDENFR, val);
    }
};
#endif //TAYILER_IDENTNODE_H
