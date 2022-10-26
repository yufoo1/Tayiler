//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCRPARAMSNODE_H
#define TAYILER_FUNCRPARAMSNODE_H

#include "../Node.h"

class FuncRParamsNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCRPARAMS, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_FUNCRPARAMSNODE_H
