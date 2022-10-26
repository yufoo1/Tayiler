//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONSTDECLNODE_H
#define TAYILER_CONSTDECLNODE_H

#include "../Node.h"

class ConstDeclNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONSTDECL, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_CONSTDECLNODE_H
