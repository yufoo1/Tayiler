//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCFPARAMNODE_H
#define TAYILER_FUNCFPARAMNODE_H

#include "../Node.h"

class FuncFParamNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCFPARAM, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_FUNCFPARAMNODE_H
