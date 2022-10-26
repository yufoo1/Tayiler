//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_IDENTNODE_H
#define TAYILER_IDENTNODE_H

#include "../Node.h"

class IdentNode: public Node {
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList, string val) override {
        parserList->emplace_back(SyntaxType::IDENFR, val);
    }

    SyntaxType getType() override {
        return SyntaxType::IDENFR;
    }

    using Node::Node;
};
#endif //TAYILER_IDENTNODE_H
