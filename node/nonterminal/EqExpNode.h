//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_EQEXPNODE_H
#define TAYILER_EQEXPNODE_H

#include "../Node.h"

class EqExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::EQEXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_EQEXPNODE_H
