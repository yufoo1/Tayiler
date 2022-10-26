//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_LBRACKNODE_H
#define TAYILER_LBRACKNODE_H

#include "../Node.h"

class LBrackNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::LBRACK, TokenMap.at(SyntaxType::LBRACK));
    }
};
#endif //TAYILER_LBRACKNODE_H
