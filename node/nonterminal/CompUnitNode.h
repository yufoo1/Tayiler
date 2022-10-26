//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_COMPUNITNODE_H
#define TAYILER_COMPUNITNODE_H

#include "../Node.h"

class CompUnitNode: public Node {
private:
    vector<Node*> decls;
    vector<Node*> funcDefs;
    Node* mainFuncDef = nullptr;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::COMPUNIT, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::COMPUNIT;
    }

    void insertNode(Node* node) override {
        switch (node->getType()) {
            case SyntaxType::DECL: decls.emplace_back(node); break;
            case SyntaxType::FUNCDEF: funcDefs.emplace_back(node); break;
            case SyntaxType::MAINFUNCDEF: assert(mainFuncDef == nullptr), mainFuncDef = node;
            default: break;
        }
    }

    vector<Node*> getDeclVec() {
        return decls;
    }

    vector<Node*> getFuncDefVec() {
        return funcDefs;
    }

    Node* getMainFuncDef() {
        return mainFuncDef;
    }

};
#endif //TAYILER_COMPUNITNODE_H
