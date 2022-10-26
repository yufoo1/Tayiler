//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_NUMBERNODE_H
#define TAYILER_NUMBERNODE_H

#include "../Node.h"

class NumberNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::NUMBER, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_NUMBERNODE_H
