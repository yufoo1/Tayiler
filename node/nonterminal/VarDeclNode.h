//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_VARDECLNODE_H
#define TAYILER_VARDECLNODE_H

#include "../Node.h"

class VarDeclNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::VARDECL, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_VARDECLNODE_H
