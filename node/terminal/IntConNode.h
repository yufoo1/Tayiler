//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_INTCONNODE_H
#define TAYILER_INTCONNODE_H

#include "../Node.h"

class IntConNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList, string val) override {
        parserList->emplace_back(SyntaxType::INTCON, val);
    }
};
#endif //TAYILER_INTCONNODE_H
