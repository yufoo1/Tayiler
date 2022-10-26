//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_BLOCKNODE_H
#define TAYILER_BLOCKNODE_H

#include "../Node.h"

class BlockNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::BLOCK, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_BLOCKNODE_H
