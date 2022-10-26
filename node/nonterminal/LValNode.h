//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LVALNODE_H
#define TAYILER_LVALNODE_H

#include "../Node.h"

class LValNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LVAL, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_LVALNODE_H
