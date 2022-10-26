//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_MULEXPNODE_H
#define TAYILER_MULEXPNODE_H

#include "../Node.h"

class MulExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::MULEXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_MULEXPNODE_H
