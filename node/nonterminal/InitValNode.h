//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_INITVALNODE_H
#define TAYILER_INITVALNODE_H

#include "../Node.h"

class InitValNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::INITVAL, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_INITVALNODE_H
