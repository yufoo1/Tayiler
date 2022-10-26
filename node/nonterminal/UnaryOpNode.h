//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_UNARYOPNODE_H
#define TAYILER_UNARYOPNODE_H

#include "../Node.h"

class UnaryOpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::UNARYOP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_UNARYOPNODE_H
