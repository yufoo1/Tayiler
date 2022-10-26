//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_MAINNODE_H
#define TAYILER_MAINNODE_H

#include "../Node.h"

class MainNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::MAINTK, "main");
    }
};
#endif //TAYILER_MAINNODE_H
