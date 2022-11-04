//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_FUNCDEFNODE_H
#define TAYILER_FUNCDEFNODE_H

#include "../Node.h"
#include "FuncTypeNode.h"
#include "FuncFParamsNode.h"
class FuncDefNode: public Node{
private:
    Node* funcType = nullptr;
    string ident;
    Node* funcFParams = nullptr;
    Node* block = nullptr;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::FUNCDEF, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::FUNCDEF;
    }

    void insertNode(Node* node) override {
        switch (node->getType()) {
            case SyntaxType::FUNCTYPE: YASSERT(funcType == nullptr) funcType = node; break;
            case SyntaxType::IDENFR: YASSERT(ident.empty()) ident = node->getVal(); break;
            case SyntaxType::FUNCFPARAMS: YASSERT(funcFParams == nullptr) funcFParams = node; break;
            case SyntaxType::BLOCK: YASSERT(block == nullptr) block = node; break;
            default: break;
        }
    }

    FuncTypeNode* getFuncType() {
        return dynamic_cast<FuncTypeNode *>(funcType);
    }

    string getIdent() {
        return ident;
    }

    FuncFParamsNode* getFunFParams() {
        return funcFParams == nullptr ? nullptr : dynamic_cast<FuncFParamsNode *>(funcFParams);
    }

    BlockNode* getBlock() {
        return dynamic_cast<BlockNode *>(block);
    }
};
#endif //TAYILER_FUNCDEFNODE_H
