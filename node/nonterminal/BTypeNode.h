//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_BTYPENODE_H
#define TAYILER_BTYPENODE_H

#include "../Node.h"

class BTypeNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
//        parserList->emplace_back(SyntaxType::BTYPE, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_BTYPENODE_H
