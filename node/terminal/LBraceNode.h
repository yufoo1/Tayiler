//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_LBRACENODE_H
#define TAYILER_LBRACENODE_H

#include "../Node.h"

class LBraceNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LBRACE, TokenMap.at(SyntaxType::LBRACE));
    }
};
#endif //TAYILER_LBRACENODE_H
