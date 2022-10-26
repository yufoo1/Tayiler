//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_STMTNODE_H
#define TAYILER_STMTNODE_H

#include "../Node.h"

class StmtNode: public Node {
private:
    Node* cond = nullptr, *lVal = nullptr, *block = nullptr;
    vector<Node*> stmts, exp;
    string* formatString = nullptr;
    StmtType stmtType = StmtType::NONE;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::STMT, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::STMT;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::IFTK: assert(stmtType == StmtType::NONE), stmtType = StmtType::IF; break;
            case SyntaxType::WHILETK: assert(stmtType == StmtType::NONE), stmtType = StmtType::WHILE; break;
            case SyntaxType::BREAKTK: assert(stmtType == StmtType::NONE), stmtType = StmtType::BREAK; break;
            case SyntaxType::CONTINUETK: assert(stmtType == StmtType::NONE), stmtType = StmtType::CONTINUE; break;
            case SyntaxType::RETURNTK: assert(stmtType == StmtType::NONE), stmtType = StmtType::RETURN; break;
            case SyntaxType::GETINTTK: assert(stmtType == StmtType::LVALASSIGN), stmtType = StmtType::GETINT; break;
            case SyntaxType::PRINTFTK: assert(stmtType == StmtType::NONE), stmtType = StmtType::PRINTF; break;
            case SyntaxType::COND: assert(cond == nullptr), cond = node; break;
            case SyntaxType::BLOCK: assert(cond == nullptr), block = node; stmtType = StmtType::BLOCK; break;
            case SyntaxType::LVAL: assert(lVal == nullptr), lVal = node; stmtType = StmtType::LVALASSIGN; break;
            case SyntaxType::STMT: stmts.emplace_back(node);
            case SyntaxType::EXP: exp.emplace_back(node); stmtType = stmtType == StmtType::NONE ? StmtType::EXP : stmtType; break;
            case SyntaxType::SEMICN: stmtType = stmtType == StmtType::NONE ? StmtType::SEMICN : stmtType; break;
            case SyntaxType::STRCON: assert(formatString == nullptr), *formatString = node->getVal(); break;
            default: break;
        }
    }
};
#endif //TAYILER_STMTNODE_H
