//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONSTINITVALNODE_H
#define TAYILER_CONSTINITVALNODE_H

#include "../Node.h"

class ConstInitValNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONSTINITVAL, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_CONSTINITVALNODE_H
