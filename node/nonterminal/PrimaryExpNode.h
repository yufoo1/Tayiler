//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_PRIMARYEXPNODE_H
#define TAYILER_PRIMARYEXPNODE_H

#include "../Node.h"

class PrimaryExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::PRIMARYEXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_PRIMARYEXPNODE_H
