//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_VOIDNODE_H
#define TAYILER_VOIDNODE_H

#include "../Node.h"

class VoidNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::VOIDTK, "void");
    }
};
#endif //TAYILER_VOIDNODE_H
