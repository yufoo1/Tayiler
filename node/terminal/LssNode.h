//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_LSSNODE_H
#define TAYILER_LSSNODE_H

#include "../Node.h"

class LssNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LSS, TokenMap.at(SyntaxType::LSS));
    }
};
#endif //TAYILER_LSSNODE_H
