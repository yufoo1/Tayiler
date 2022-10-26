//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_VARDEFNODE_H
#define TAYILER_VARDEFNODE_H

#include "../Node.h"

class VarDefNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::VARDEF, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_VARDEFNODE_H
