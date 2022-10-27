//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_PRIMARYEXPNODE_H
#define TAYILER_PRIMARYEXPNODE_H

#include "../Node.h"

class PrimaryExpNode: public Node {
private:
    Node* exp = nullptr;
    Node* lVal = nullptr;
    Node* number = nullptr;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::PRIMARYEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::PRIMARYEXP;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::EXP: assert(lVal == nullptr && number == nullptr), exp = node; break;
            case SyntaxType::LVAL: assert(exp == nullptr && number == nullptr), lVal = node; break;
            case SyntaxType::NUMBER: assert(exp == nullptr && lVal == nullptr), number = node; break;
            default: break;
        }
    }

    ExpNode* getExp() {
        return dynamic_cast<ExpNode *>(exp);
    }

    LValNode* getLVal() {
        return dynamic_cast<LValNode *>(lVal);
    }

    NumberNode* getNumber() {
        return dynamic_cast<NumberNode *>(number);
    }
};
#endif //TAYILER_PRIMARYEXPNODE_H
