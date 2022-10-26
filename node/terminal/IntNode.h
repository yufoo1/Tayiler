//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_INTNODE_H
#define TAYILER_INTNODE_H

#include "../Node.h"

class IntNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::INTTK, "int");
    }
};
#endif //TAYILER_INTNODE_H
