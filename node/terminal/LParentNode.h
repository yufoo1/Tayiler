//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_LPARENTNODE_H
#define TAYILER_LPARENTNODE_H

#include "../Node.h"

class LParentNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LPARENT, TokenMap.at(SyntaxType::LPARENT));
    }
};
#endif //TAYILER_LPARENTNODE_H
