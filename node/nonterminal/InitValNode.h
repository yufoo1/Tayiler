//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_INITVALNODE_H
#define TAYILER_INITVALNODE_H

#include "../Node.h"

class InitValNode: public Node {
private:
    Node* exp = nullptr;
    vector<Node*> initVals;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::INITVAL, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::INITVAL;
    }
    
    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::EXP: assert(initVals.empty() && exp == nullptr), exp = node; break;
            case SyntaxType::INITVAL: assert(exp == nullptr), initVals.emplace_back(node); break;
            default: break;
        }
    }

    Node* getExp() {
        return exp;
    }

    vector<Node*> getInitVals() {
        return initVals;
    }


};
#endif //TAYILER_INITVALNODE_H
