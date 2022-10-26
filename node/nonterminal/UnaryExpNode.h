//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_UNARYEXPNODE_H
#define TAYILER_UNARYEXPNODE_H

#include "../Node.h"

class UnaryExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::UNARYEXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_UNARYEXPNODE_H
