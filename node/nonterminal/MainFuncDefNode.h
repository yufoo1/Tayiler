//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_MAINFUNCDEFNODE_H
#define TAYILER_MAINFUNCDEFNODE_H

#include "../Node.h"

class MainFuncDefNode: public Node {
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::MAINFUNCDEF, SyntaxType2String.at(SyntaxType::NONE));
    }
};
#endif //TAYILER_MAINFUNCDEFNODE_H
