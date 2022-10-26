//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LANDEXPNODE_H
#define TAYILER_LANDEXPNODE_H

#include "../Node.h"

class LAndExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LANDEXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_LANDEXPNODE_H
