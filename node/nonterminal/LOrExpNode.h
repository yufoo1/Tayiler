//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LOREXPNODE_H
#define TAYILER_LOREXPNODE_H

#include "../Node.h"

class LOrExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LOREXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_LOREXPNODE_H
