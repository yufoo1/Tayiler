//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_NOTNODE_H
#define TAYILER_NOTNODE_H

#include "../Node.h"

class NotNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::NOT, TokenMap.at(SyntaxType::NOT));
    }
};
#endif //TAYILER_NOTNODE_H
