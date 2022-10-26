//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_STMTNODE_H
#define TAYILER_STMTNODE_H

#include "../Node.h"

class StmtNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::STMT, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_STMTNODE_H
