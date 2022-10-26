//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_PLUSNODE_H
#define TAYILER_PLUSNODE_H

#include "../Node.h"

class PlusNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::PLUS, TokenMap.at(SyntaxType::PLUS));
    }
};
#endif //TAYILER_PLUSNODE_H
