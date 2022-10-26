//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCFPARAMSNODE_H
#define TAYILER_FUNCFPARAMSNODE_H

#include "../Node.h"

class FuncFParamsNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCFPARAMS, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_FUNCFPARAMSNODE_H
