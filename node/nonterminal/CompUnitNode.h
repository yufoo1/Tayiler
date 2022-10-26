//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_COMPUNITNODE_H
#define TAYILER_COMPUNITNODE_H

#include "../Node.h"

class CompUnitNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::COMPUNIT, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_COMPUNITNODE_H
