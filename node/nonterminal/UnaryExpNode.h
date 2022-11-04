//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_UNARYEXPNODE_H
#define TAYILER_UNARYEXPNODE_H

#include "../Node.h"
#include "UnaryOpNode.h"

class UnaryExpNode: public Node {
private:
    Node* primaryExp = nullptr;
    string ident;
    Node* funcRParams = nullptr;
    SyntaxType unaryOp = SyntaxType::NONE;
    Node* unaryExp = nullptr;

public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::UNARYEXP, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::UNARYEXP;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::PRIMARYEXP: YASSERT(funcRParams == nullptr && ident.empty()) primaryExp = node; break;
            case SyntaxType::IDENFR: YASSERT(primaryExp == nullptr) ident = node->getVal(); break;
            case SyntaxType::FUNCRPARAMS: YASSERT(primaryExp == nullptr) funcRParams = node; break;
            case SyntaxType::UNARYOP: YASSERT(unaryOp == SyntaxType::NONE && ident.empty()) unaryOp = dynamic_cast<UnaryOpNode*>(node)->getTokenType(); break;
            case SyntaxType::UNARYEXP: YASSERT(unaryExp == nullptr && ident.empty()) unaryExp = node; break;
            default: break;
        }
    }

    PrimaryExpNode* getPrimaryExp() {
        return dynamic_cast<PrimaryExpNode *>(primaryExp);
    }

    string getIdent() {
        return ident;
    }

    FuncRParamsNode* getFuncRParams() {
        return dynamic_cast<FuncRParamsNode *>(funcRParams);
    }

    SyntaxType getUnaryOp() {
        return unaryOp;
    }

    UnaryExpNode* getUnaryExp() {
        return dynamic_cast<UnaryExpNode *>(unaryExp);
    }
};
#endif //TAYILER_UNARYEXPNODE_H
