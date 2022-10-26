//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_ADDEXPNODE_H
#define TAYILER_ADDEXPNODE_H

#include "../Node.h"

class AddExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::ADDEXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_ADDEXPNODE_H
