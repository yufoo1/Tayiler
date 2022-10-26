//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_VISITOR_H
#define TAYILER_VISITOR_H

#include "../node/Node.h"
#include "Manager.h"

class Visitor {
public:
    Visitor(Node* root) {
        manage = new Manager;
    }

private:
    Manager* manage;

    void visitAst(Node* root) {
        visitCompUnit(dynamic_cast<CompUnitNode *>(root));
    }

    void visitCompUnit(CompUnitNode* node) {
        for (auto i : (node->getDeclVec())) visitDecl(dynamic_cast<DeclNode *>(i));
        for (auto i : (node->getFuncDefVec())) visitFuncDef(dynamic_cast<FuncDefNode *>(i));
        visitMainFuncDef(node->getMainFuncDef());
    }

    void visitDecl(DeclNode* node) {

    }

    void visitFuncDef(FuncDefNode* node) {

        string ident = node->getVal();
    }

    void visitMainFuncDef(MainFuncDefNode* node) {
        node->getBlock();
    }


    void error() {
        cout << "error!" << "\n";
    }
};
#endif //TAYILER_VISITOR_H
