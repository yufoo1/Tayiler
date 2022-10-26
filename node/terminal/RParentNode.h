//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_RPARENTNODE_H
#define TAYILER_RPARENTNODE_H

#include "../Node.h"

class RParentNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::RPARENT, TokenMap.at(SyntaxType::RPARENT));
    }

    SyntaxType getType() override {
        return SyntaxType::RPARENT;
    }
};
#endif //TAYILER_RPARENTNODE_H
