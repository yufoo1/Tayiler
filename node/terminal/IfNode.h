//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_IFNODE_H
#define TAYILER_IFNODE_H

#include "../Node.h"

class IfNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::IFTK, "if");
    }
};
#endif //TAYILER_IFNODE_H
