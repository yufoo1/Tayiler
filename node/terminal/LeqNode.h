//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_LEQNODE_H
#define TAYILER_LEQNODE_H

#include "../Node.h"

class LeqNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LEQ, TokenMap.at(SyntaxType::LEQ));
    }

    SyntaxType getType() override {
        return SyntaxType::LEQ;
    }
};
#endif //TAYILER_LEQNODE_H
