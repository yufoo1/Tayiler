//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_VISITOR_H
#define TAYILER_VISITOR_H

#include "../node/Node.h"
#include "Manager.h"

class Visitor {
public:
    Visitor() {
        manage = new Manager;
    }

private:
    Manager* manage;

    void visitAst(Node* root) {
        visitCompUnit(root);
    }

    void visitCompUnit(Node* node) {
//        for (auto i : node->getNodes()) {
//            switch (i->getType()) {
//                case SyntaxType::DECL: visitDecl(i); break;
//                case SyntaxType::FUNCDEF: visitFuncDef(i); break;
//                case SyntaxType::MAINFUNCDEF: visitMainFuncDef(i); break;
//                default: error(); break;
//            }
//        }
    }

    void visitDecl(Node* node) {

    }

    void visitFuncDef(Node* node) {

        string ident = node->getVal();
    }

    void visitMainFuncDef(Node* node) {

    }


    void error() {
        cout << "error!" << "\n";
    }
};
#endif //TAYILER_VISITOR_H
