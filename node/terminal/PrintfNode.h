//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_PRINTFNODE_H
#define TAYILER_PRINTFNODE_H

#include "../Node.h"

class PrintfNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::PRINTFTK, "printf");
    }

    SyntaxType getType() override {
        return SyntaxType::PRINTFTK;
    }
};
#endif //TAYILER_PRINTFNODE_H
