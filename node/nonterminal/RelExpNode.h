//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_RELEXPNODE_H
#define TAYILER_RELEXPNODE_H

#include "../Node.h"

class RelExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::RELEXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_RELEXPNODE_H
