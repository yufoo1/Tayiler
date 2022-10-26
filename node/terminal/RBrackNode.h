//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_RBRACKNODE_H
#define TAYILER_RBRACKNODE_H

#include "../Node.h"

class RBrackNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::RBRACK, TokenMap.at(SyntaxType::RBRACK));
    }

    SyntaxType getType() override {
        return SyntaxType::RBRACK;
    }
};
#endif //TAYILER_RBRACKNODE_H
