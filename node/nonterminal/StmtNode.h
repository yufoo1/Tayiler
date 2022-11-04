//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_STMTNODE_H
#define TAYILER_STMTNODE_H

#include "../Node.h"

class StmtNode: public Node {
private:
    Node* cond = nullptr, *lVal = nullptr, *block = nullptr;
    vector<ExpNode*> exps;
    vector<StmtNode *> stmts;
    string formatString;
    StmtType stmtType = StmtType::NONE;
public:
    void insertList(vector<tuple<SyntaxType, string>>* parserList) override {
        parserList->emplace_back(SyntaxType::STMT, SyntaxType2String.at(SyntaxType::NONE));
    }

    SyntaxType getType() override {
        return SyntaxType::STMT;
    }

    StmtType getStmtType() {
        return stmtType;
    }

    void insertNode(Node *node) override {
        switch (node->getType()) {
            case SyntaxType::IFTK: YASSERT(stmtType == StmtType::NONE) stmtType = StmtType::IF; break;
            case SyntaxType::WHILETK: YASSERT(stmtType == StmtType::NONE) stmtType = StmtType::WHILE; break;
            case SyntaxType::BREAKTK: YASSERT(stmtType == StmtType::NONE) stmtType = StmtType::BREAK; break;
            case SyntaxType::CONTINUETK: YASSERT(stmtType == StmtType::NONE) stmtType = StmtType::CONTINUE; break;
            case SyntaxType::RETURNTK: YASSERT(stmtType == StmtType::NONE) stmtType = StmtType::RETURN; break;
            case SyntaxType::GETINTTK: YASSERT(stmtType == StmtType::LVALASSIGN) stmtType = StmtType::GETINT; break;
            case SyntaxType::PRINTFTK: YASSERT(stmtType == StmtType::NONE) stmtType = StmtType::PRINTF; break;
            case SyntaxType::COND: YASSERT(cond == nullptr) cond = node; break;
            case SyntaxType::BLOCK: YASSERT(cond == nullptr) block = node; stmtType = StmtType::BLOCK; break;
            case SyntaxType::LVAL: YASSERT(lVal == nullptr) lVal = node; stmtType = StmtType::LVALASSIGN; break;
            case SyntaxType::STMT: stmts.emplace_back(dynamic_cast<StmtNode *>(node));
            case SyntaxType::EXP: exps.emplace_back(dynamic_cast<ExpNode *>(node)); stmtType = stmtType == StmtType::NONE ? StmtType::EXP : stmtType; break;
            case SyntaxType::SEMICN: stmtType = stmtType == StmtType::NONE ? StmtType::SEMICN : stmtType; break;
            case SyntaxType::STRCON: YASSERT(formatString.empty()) formatString = node->getVal(); break;
            default: break;
        }
    }

    CondNode* getCond() {
        return dynamic_cast<CondNode *>(cond);
    }

    LValNode* getLVal() {
        return dynamic_cast<LValNode *>(lVal);
    }

    BlockNode* getBlock() {
        return dynamic_cast<BlockNode *>(block);
    }

    vector<StmtNode*> getStmts() {
        return stmts;
    }

    vector<ExpNode*> getExps() {
        return exps;
    }

    string getFormatString() {
        return formatString;
    }
};
#endif //TAYILER_STMTNODE_H
