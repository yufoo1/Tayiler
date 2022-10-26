//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_WHILENODE_H
#define TAYILER_WHILENODE_H

#include "../Node.h"

class WhileNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::WHILETK, "while");
    }

    SyntaxType getType() override {
        return SyntaxType::WHILETK;
    }
};
#endif //TAYILER_WHILENODE_H
