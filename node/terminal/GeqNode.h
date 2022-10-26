//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_GEQNODE_H
#define TAYILER_GEQNODE_H

#include "../Node.h"

class GeqNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::GEQ, TokenMap.at(SyntaxType::GEQ));
    }
};
#endif //TAYILER_GEQNODE_H
