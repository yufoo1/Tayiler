//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCTYPENODE_H
#define TAYILER_FUNCTYPENODE_H

#include "../Node.h"

class FuncTypeNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCTYPE, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_FUNCTYPENODE_H
