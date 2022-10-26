//
// Created by yufoo1 on 2022/10/25.
//

#ifndef TAYILER_SYNTAXTREE_H
#define TAYILER_SYNTAXTREE_H

#include "../node/Node.h"
#include "../node/nonterminal/CompUnitNode.h"
#include "../node/nonterminal/FuncDefNode.h"
#include "../node/nonterminal/FuncTypeNode.h"
#include "../node/nonterminal/AddConstExpNode.h"
#include "../node/nonterminal/AddExpNode.h"
#include "../node/nonterminal/BlockItemNode.h"
#include "../node/nonterminal/BlockNode.h"
#include "../node/nonterminal/BTypeNode.h"
#include "../node/nonterminal/CondNode.h"
#include "../node/nonterminal/ConstDeclNode.h"
#include "../node/nonterminal/ConstDefNode.h"
#include "../node/nonterminal/ConstExpNode.h"
#include "../node/nonterminal/ConstInitValNode.h"
#include "../node/nonterminal/DeclNode.h"
#include "../node/nonterminal/EqExpNode.h"
#include "../node/nonterminal/ExpNode.h"
#include "../node/nonterminal/FuncFParamNode.h"
#include "../node/nonterminal/FuncFParamsNode.h"
#include "../node/nonterminal/FuncRParamsNode.h"
#include "../node/terminal/IdentNode.h"
#include "../node/nonterminal/InitValNode.h"
#include "../node/nonterminal/IntConstNode.h"
#include "../node/nonterminal/LAndExpNode.h"
#include "../node/nonterminal/LOrExpNode.h"
#include "../node/nonterminal/LValNode.h"
#include "../node/nonterminal/MainFuncDefNode.h"
#include "../node/nonterminal/MulExpNode.h"
#include "../node/nonterminal/NumberNode.h"
#include "../node/nonterminal/PrimaryExpNode.h"
#include "../node/nonterminal/RelExpNode.h"
#include "../node/nonterminal/StmtNode.h"
#include "../node/nonterminal/UnaryExpNode.h"
#include "../node/nonterminal/UnaryOpNode.h"
#include "../node/nonterminal/VarDeclNode.h"
#include "../node/nonterminal/VarDefNode.h"
#include "../node/terminal/AndNode.h"
#include "../node/terminal/AssignNode.h"
#include "../node/terminal/BreakNode.h"
#include "../node/terminal/CommaNode.h"
#include "../node/terminal/ConstNode.h"
#include "../node/terminal/ContinueNode.h"
#include "../node/terminal/DivNode.h"
#include "../node/terminal/ElseNode.h"
#include "../node/terminal/EqlNode.h"
#include "../node/terminal/GeqNode.h"
#include "../node/terminal/GetintNode.h"
#include "../node/terminal/GreNode.h"
#include "../node/terminal/IfNode.h"
#include "../node/terminal/IntConNode.h"
#include "../node/terminal/IntNode.h"
#include "../node/terminal/LBraceNode.h"
#include "../node/terminal/LBrackNode.h"
#include "../node/terminal/LeqNode.h"
#include "../node/terminal/LParentNode.h"
#include "../node/terminal/LssNode.h"
#include "../node/terminal/MainNode.h"
#include "../node/terminal/MinuNode.h"
#include "../node/terminal/ModNode.h"
#include "../node/terminal/MultNode.h"
#include "../node/terminal/NeqNode.h"
#include "../node/terminal/NotNode.h"
#include "../node/nonterminal/NumberNode.h"
#include "../node/terminal/OrNode.h"
#include "../node/terminal/PlusNode.h"
#include "../node/terminal/PrintfNode.h"
#include "../node/terminal/RBraceNode.h"
#include "../node/terminal/RBrackNode.h"
#include "../node/terminal/ReturnNode.h"
#include "../node/terminal/RParentNode.h"
#include "../node/terminal/SemicnNode.h"
#include "../node/terminal/StrConNode.h"
#include "../node/terminal/VoidNode.h"
#include "../node/terminal/WhileNode.h"

class SyntaxTree {
private:
    Node* root;
public:
    explicit SyntaxTree(Node* root) {
        this->root = root;
    }

    Node* getRoot() {
        return root;
    }
};
#endif //TAYILER_SYNTAXTREE_H
