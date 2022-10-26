//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_CONSTDEFNODE_H
#define TAYILER_CONSTDEFNODE_H

#include "../Node.h"

class ConstDefNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONSTDEF, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_CONSTDEFNODE_H
