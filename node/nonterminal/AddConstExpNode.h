//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_ADDCONSTEXPNODE_H
#define TAYILER_ADDCONSTEXPNODE_H

#include "../Node.h"

class AddConstExpNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::ADDCONSTEXP, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_ADDCONSTEXPNODE_H
