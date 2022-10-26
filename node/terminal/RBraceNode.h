//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_RBRACENODE_H
#define TAYILER_RBRACENODE_H

#include "../Node.h"

class RBraceNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::RBRACE, TokenMap.at(SyntaxType::RBRACE));
    }
};
#endif //TAYILER_RBRACENODE_H
