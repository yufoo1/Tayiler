//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_MINUNODE_H
#define TAYILER_MINUNODE_H

#include "../Node.h"

class MinuNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::MINU, TokenMap.at(SyntaxType::MINU));
    }
};
#endif //TAYILER_MINUNODE_H
