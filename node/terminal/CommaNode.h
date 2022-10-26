//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_COMMANODE_H
#define TAYILER_COMMANODE_H

#include "../Node.h"

class CommaNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::COMMA, TokenMap.at(SyntaxType::COMMA));
    }

    SyntaxType getType() override {
        return SyntaxType::COMMA;
    }
};
#endif //TAYILER_COMMANODE_H
