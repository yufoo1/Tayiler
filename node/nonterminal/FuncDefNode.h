//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCDEFNODE_H
#define TAYILER_FUNCDEFNODE_H

#include "../Node.h"

class FuncDefNode: public Node{
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCDEF, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_FUNCDEFNODE_H
