//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_CONTINUENODE_H
#define TAYILER_CONTINUENODE_H

#include "../Node.h"

class ContinueNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::CONTINUETK, "continue");
    }

    SyntaxType getType() override {
        return SyntaxType::CONTINUETK;
    }
};
#endif //TAYILER_CONTINUENODE_H
