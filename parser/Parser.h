//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_PARSER_H
#define TAYILER_PARSER_H

#include <utility>
#include <vector>
#include "map"
#include "set"
#include "iostream"
#include "ParseCursor.h"
#include "SyntaxTree.h"

using namespace std;
class Parser {
private:
    vector<tuple<SyntaxType, string>> parserList;
    ParseCursor* cursor;
    SyntaxTree* syntaxTree;

    void compUnit(Node* curNode) {
        while (!cursor->judgeEnd()) {
            switch (get<0>(cursor->getNthNode(0))) {
                case SyntaxType::CONSTTK: genNode(curNode, SyntaxType::DECL); break;
                case SyntaxType::VOIDTK: genNode(curNode, SyntaxType::FUNCDEF); break;
                case SyntaxType::INTTK: {
                    if (get<0>(cursor->getNthNode(1)) == SyntaxType::IDENFR && get<0>(cursor->getNthNode(2)) == SyntaxType::LPARENT) genNode(curNode, SyntaxType::FUNCDEF);
                    else if (get<0>(cursor->getNthNode(1)) == SyntaxType::MAINTK) genNode(curNode, SyntaxType::MAINFUNCDEF);
                    else genNode(curNode, SyntaxType::DECL);
                    break;
                }
                default: break;
            }
        }
        syntaxTree->getRoot()->insertList(&parserList);
    }

    void funcDef(Node* curNode) {
        genNode(curNode, SyntaxType::FUNCTYPE);
        genNode(curNode, SyntaxType::IDENFR);
        genNode(curNode, SyntaxType::LPARENT);
        if (get<0>(cursor->getNthNode(0)) == SyntaxType::INTTK) genNode(curNode, SyntaxType::FUNCFPARAMS);
        genNode(curNode, SyntaxType::RPARENT);
        genNode(curNode, SyntaxType::BLOCK);
    }


    void funcType(Node* curNode) {
        switch (get<0>(cursor->getNthNode(0))) {
            case SyntaxType::VOIDTK: genNode(curNode, SyntaxType::VOIDTK); break;
            case SyntaxType::INTTK: genNode(curNode, SyntaxType::INTTK); break;
            default: error();
        }
    }

    void funcFParams(Node* curNode) {
        genNode(curNode, SyntaxType::FUNCFPARAM);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::COMMA) {
            genNode(curNode, SyntaxType::COMMA);
            genNode(curNode, SyntaxType::FUNCFPARAM);
        }
    }

    void funcFParam(Node* curNode) {
        genNode(curNode, SyntaxType::BTYPE);
        genNode(curNode, SyntaxType::IDENFR);
        if (get<0>(cursor->getNthNode(0)) == SyntaxType::LBRACK) {
            genNode(curNode, SyntaxType::LBRACK);
            genNode(curNode, SyntaxType::RBRACK);
            while (get<0>(cursor->getNthNode(0)) == SyntaxType::LBRACK) {
                genNode(curNode, SyntaxType::LBRACK);
                genNode(curNode, SyntaxType::CONSTEXP);
                genNode(curNode, SyntaxType::RBRACK);
            }
        }
    }



    void block(Node* curNode) {
        genNode(curNode, SyntaxType::LBRACE);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::CONSTTK || get<0>(cursor->getNthNode(0)) == SyntaxType::INTTK ||
               StmtFirst.count(get<0>(cursor->getNthNode(0)))) {
            genNode(curNode, SyntaxType::BLOCKITEM);
        }
        genNode(curNode, SyntaxType::RBRACE);
    }

    void blockItem(Node* curNode) {
        if (get<0>(cursor->getNthNode(0)) == SyntaxType::CONSTTK || get<0>(cursor->getNthNode(0)) == SyntaxType::INTTK) {
            genNode(curNode, SyntaxType::DECL);
        } else if (StmtFirst.count(get<0>(cursor->getNthNode(0)))) {
            genNode(curNode, SyntaxType::STMT);
        } else {
            error();
        }
    }

    void stmt(Node* curNode) {
        switch (get<0>(cursor->getNthNode(0))) {
            case SyntaxType::LBRACE: genNode(curNode, SyntaxType::BLOCK); break;
            case SyntaxType::IFTK: {
                genNode(curNode, SyntaxType::IFTK);
                genNode(curNode, SyntaxType::LPARENT);
                genNode(curNode, SyntaxType::COND);
                genNode(curNode, SyntaxType::RPARENT);
                genNode(curNode, SyntaxType::STMT);
                if (get<0>(cursor->getNthNode(0)) == SyntaxType::ELSETK) {
                    genNode(curNode, SyntaxType::ELSETK);
                    genNode(curNode, SyntaxType::STMT);
                }
                break;
            }
            case SyntaxType::WHILETK: {
                genNode(curNode, SyntaxType::WHILETK);
                genNode(curNode, SyntaxType::LPARENT);
                genNode(curNode, SyntaxType::COND);
                genNode(curNode, SyntaxType::RPARENT);
                genNode(curNode, SyntaxType::STMT);
                break;
            }
            case SyntaxType::BREAKTK: {
                genNode(curNode, SyntaxType::BREAKTK);
                genNode(curNode, SyntaxType::SEMICN);
                break;
            }
            case SyntaxType::CONTINUETK: {
                genNode(curNode, SyntaxType::CONTINUETK);
                genNode(curNode, SyntaxType::SEMICN);
                break;
            }
            case SyntaxType::RETURNTK: {
                genNode(curNode, SyntaxType::RETURNTK);
                if (ExpFirst.count(get<0>(cursor->getNthNode(0)))) {
                    genNode(curNode, SyntaxType::EXP);
                }
                genNode(curNode, SyntaxType::SEMICN);
                break;
            }
            case SyntaxType::PRINTFTK: {
                genNode(curNode, SyntaxType::PRINTFTK);
                genNode(curNode, SyntaxType::LPARENT);
                genNode(curNode, SyntaxType::STRCON);
                while (get<0>(cursor->getNthNode(0)) == SyntaxType::COMMA) {
                    genNode(curNode, SyntaxType::COMMA);
                    genNode(curNode, SyntaxType::EXP);
                }
                genNode(curNode, SyntaxType::RPARENT);
                genNode(curNode, SyntaxType::SEMICN);
                break;
            }
            default: {
                if (get<0>(cursor->getNthNode(0)) == SyntaxType::IDENFR && judgeLVal()) {
                    genNode(curNode, SyntaxType::LVAL);genNode(curNode, SyntaxType::ASSIGN);
                    if (get<0>(cursor->getNthNode(0)) == SyntaxType::GETINTTK) {
                        genNode(curNode, SyntaxType::GETINTTK);
                        genNode(curNode, SyntaxType::LPARENT);
                        genNode(curNode, SyntaxType::RPARENT);
                    } else if (ExpFirst.count(get<0>(cursor->getNthNode(0)))) {
                        genNode(curNode, SyntaxType::EXP);
                    } else {
                        error();
                    }
                    genNode(curNode, SyntaxType::SEMICN);
                } else if (ExpFirst.count(get<0>(cursor->getNthNode(0))) && !judgeLVal()) {
                    genNode(curNode, SyntaxType::EXP);
                    genNode(curNode, SyntaxType::SEMICN);
                } else if (get<0>(cursor->getNthNode(0)) == SyntaxType::SEMICN) {
                    genNode(curNode, SyntaxType::SEMICN);
                } else {
                    error();
                }
            }
        }
    }

    bool judgeLVal() {
        int cur = 1, lBrackCnt = 0;
        if (get<0>(cursor->getNthNode(cur)) == SyntaxType::LBRACK) {
            lBrackCnt++, cur++;
            while (lBrackCnt != 0 || get<0>(cursor->getNthNode(cur)) == SyntaxType::LBRACK) {
                if (get<0>(cursor->getNthNode(cur)) == SyntaxType::LBRACK) {
                    lBrackCnt ++;
                } else if (get<0>(cursor->getNthNode(cur)) == SyntaxType::RBRACK) {
                    lBrackCnt --;
                }
                cur++;
            }
        }
        return get<0>(cursor->getNthNode(cur)) == SyntaxType::ASSIGN;
    }

    void cond(Node* curNode) {
        genNode(curNode, SyntaxType::LOREXP);
    }

    void decl(Node* curNode) {
        switch (get<0>(cursor->getNthNode(0))) {
            case SyntaxType::CONSTTK: genNode(curNode, SyntaxType::CONSTDECL); break;
            case SyntaxType::INTTK: genNode(curNode, SyntaxType::VARDECL); break;
            default: error();
        }
    }

    void mainFuncDef(Node* curNode) {
        genNode(curNode, SyntaxType::INTTK);
        genNode(curNode, SyntaxType::MAINTK);
        genNode(curNode, SyntaxType::LPARENT);
        genNode(curNode, SyntaxType::RPARENT);
        genNode(curNode, SyntaxType::BLOCK);
    }

    void constDecl(Node* curNode) {
        genNode(curNode, SyntaxType::CONSTTK);
        genNode(curNode, SyntaxType::BTYPE);
        genNode(curNode, SyntaxType::CONSTDEF);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::COMMA) {
            genNode(curNode, SyntaxType::COMMA);
            genNode(curNode, SyntaxType::CONSTDEF);
        }
        genNode(curNode, SyntaxType::SEMICN);
    }

    void varDecl(Node* curNode) {
        genNode(curNode, SyntaxType::BTYPE);
        genNode(curNode, SyntaxType::VARDEF);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::COMMA) {
            genNode(curNode, SyntaxType::COMMA);
            genNode(curNode, SyntaxType::VARDEF);
        }
        genNode(curNode, SyntaxType::SEMICN);
    }

    void bType(Node* curNode) {
        genNode(curNode, SyntaxType::INTTK);
    }

    void constDef(Node* curNode) {
        genNode(curNode, SyntaxType::IDENFR);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::LBRACK) {
            genNode(curNode, SyntaxType::LBRACK);
            genNode(curNode, SyntaxType::CONSTEXP);
            genNode(curNode, SyntaxType::RBRACK);
        }
        genNode(curNode, SyntaxType::ASSIGN);
        genNode(curNode, SyntaxType::CONSTINITVAL);
    }

    void constExp(Node* curNode) {
        genNode(curNode, SyntaxType::ADDEXP);
    }

    void addConstExp(Node* curNode) {
        set<SyntaxType> First = {
                SyntaxType::PLUS, SyntaxType::MINU, SyntaxType::NOT
        };
        while (First.count(get<0>(cursor->getNthNode(0)))) {
            switch (get<0>(cursor->getNthNode(0))) {
                case SyntaxType::PLUS: genNode(curNode, SyntaxType::PLUS); break;
                case SyntaxType::MINU: genNode(curNode, SyntaxType::MINU); break;
                case SyntaxType::NOT: genNode(curNode, SyntaxType::NOT); break;
                default: error();
            }
            genNode(curNode, SyntaxType::MULEXP);
        }
    }

    void constInitVal(Node* curNode) {
        if (get<0>(cursor->getNthNode(0)) == SyntaxType::LBRACE) {
            genNode(curNode, SyntaxType::LBRACE);
            if (ExpFirst.count(get<0>(cursor->getNthNode(0))) || get<0>(cursor->getNthNode(0)) == SyntaxType::LBRACE) {
                genNode(curNode, SyntaxType::CONSTINITVAL);
                while (get<0>(cursor->getNthNode(0)) == SyntaxType::COMMA) {
                    genNode(curNode, SyntaxType::COMMA);
                    genNode(curNode, SyntaxType::CONSTINITVAL);
                }
            }
            genNode(curNode, SyntaxType::RBRACE);
        } else if (ExpFirst.count(get<0>(cursor->getNthNode(0)))) {
            genNode(curNode, SyntaxType::CONSTEXP);
        } else {
            error();
        }
    }

    void varDef(Node* curNode) {
        genNode(curNode, SyntaxType::IDENFR);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::LBRACK) {
            genNode(curNode, SyntaxType::LBRACK);
            genNode(curNode, SyntaxType::CONSTEXP);
            genNode(curNode, SyntaxType::RBRACK);
        }
        if (get<0>(cursor->getNthNode(0)) == SyntaxType::ASSIGN) {
            genNode(curNode, SyntaxType::ASSIGN);
            genNode(curNode, SyntaxType::INITVAL);
        }
    }

    void initVal(Node* curNode) {
        if (get<0>(cursor->getNthNode(0)) == SyntaxType::LBRACE) {
            genNode(curNode, SyntaxType::LBRACE);
            genNode(curNode, SyntaxType::INITVAL);
            while (get<0>(cursor->getNthNode(0)) == SyntaxType::COMMA) {
                genNode(curNode, SyntaxType::COMMA);
                genNode(curNode, SyntaxType::INITVAL);
            }
            genNode(curNode, SyntaxType::RBRACE);
        } else if (ExpFirst.count(get<0>(cursor->getNthNode(0)))) {
            genNode(curNode, SyntaxType::EXP);
        } else {
            error();
        }
    }

    void exp(Node* curNode) {
        genNode(curNode, SyntaxType::ADDEXP);
    }

    void lVal(Node* curNode) {
        genNode(curNode, SyntaxType::IDENFR);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::LBRACK) {
            genNode(curNode, SyntaxType::LBRACK);
            genNode(curNode, SyntaxType::EXP);
            genNode(curNode, SyntaxType::RBRACK);
        }
    }

    void primaryExp(Node* curNode) {
        switch (get<0>(cursor->getNthNode(0))) {
            case SyntaxType::INTCON: genNode(curNode, SyntaxType::NUMBER); break;
            case SyntaxType::LPARENT: {
                genNode(curNode, SyntaxType::LPARENT);
                genNode(curNode, SyntaxType::EXP);
                genNode(curNode, SyntaxType::RPARENT);
                break;
            }
            case SyntaxType::IDENFR: genNode(curNode, SyntaxType::LVAL); break;
            default: error();
        }
    }

    void number(Node* curNode) {
        genNode(curNode, SyntaxType::INTCON);
    }

    void unaryExp(Node* curNode) {
        set<SyntaxType> First = {
                SyntaxType::PLUS, SyntaxType::MINU, SyntaxType::NOT
        };
        switch (get<0>(cursor->getNthNode(0))) {
            case SyntaxType::IDENFR: {
                if (get<0>(cursor->getNthNode(1)) == SyntaxType::LPARENT) {
                    genNode(curNode, SyntaxType::IDENFR);
                    genNode(curNode, SyntaxType::LPARENT);
                    if (ExpFirst.count(get<0>(cursor->getNthNode(0)))) {
                        genNode(curNode, SyntaxType::FUNCRPARAMS);
                    }
                    genNode(curNode, SyntaxType::RPARENT);
                } else {
                    genNode(curNode, SyntaxType::PRIMARYEXP);
                }
                break;
            }
            case SyntaxType::LPARENT:
            case SyntaxType::INTCON: genNode(curNode, SyntaxType::PRIMARYEXP); break;
            default: {
                if (First.count(get<0>(cursor->getNthNode(0)))) {
                    genNode(curNode, SyntaxType::UNARYOP);
                    genNode(curNode, SyntaxType::UNARYEXP);
                } else {
                    error();
                }
            }
        }
    }

    void funcRParams(Node* curNode) {
        genNode(curNode, SyntaxType::EXP);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::COMMA) {
            genNode(curNode, SyntaxType::COMMA);
            genNode(curNode, SyntaxType::EXP);
        }
    }

    void unaryOp(Node* curNode) {
        switch (get<0>(cursor->getNthNode(0))) {
            case SyntaxType::PLUS: genNode(curNode, SyntaxType::PLUS); break;
            case SyntaxType::MINU: genNode(curNode, SyntaxType::MINU); break;
            case SyntaxType::NOT: genNode(curNode, SyntaxType::NOT); break;
            default: error();
        }
    }

    void addExp(Node* curNode) {
        set<SyntaxType> First = {
                SyntaxType::PLUS, SyntaxType::MINU, SyntaxType::NOT
        };
        genNode(curNode, SyntaxType::MULEXP);
        while (First.count(get<0>(cursor->getNthNode(0)))) {
            parserList.emplace_back(SyntaxType::ADDEXP, SyntaxType2String.at(SyntaxType::NONE));
            switch (get<0>(cursor->getNthNode(0))) {
                case SyntaxType::PLUS: genNode(curNode, SyntaxType::PLUS); break;
                case SyntaxType::MINU: genNode(curNode, SyntaxType::MINU); break;
                case SyntaxType::NOT: genNode(curNode, SyntaxType::NOT); break;
                default: error();
            }
            genNode(curNode, SyntaxType::MULEXP);
        }
    }

    void mulExp(Node* curNode) {
        set<SyntaxType> First = {
                SyntaxType::MULT, SyntaxType::DIV, SyntaxType::MOD
        };
        genNode(curNode, SyntaxType::UNARYEXP);
        while (First.count(get<0>(cursor->getNthNode(0)))) {
            parserList.emplace_back(SyntaxType::MULEXP, SyntaxType2String.at(SyntaxType::NONE));
            switch (get<0>(cursor->getNthNode(0))) {
                case SyntaxType::MULT: genNode(curNode, SyntaxType::MULT); break;
                case SyntaxType::DIV: genNode(curNode, SyntaxType::DIV); break;
                case SyntaxType::MOD: genNode(curNode, SyntaxType::MOD); break;
                default: error();
            }
            genNode(curNode, SyntaxType::UNARYEXP);
        }
    }

    void relExp(Node* curNode) {
        set<SyntaxType> First = {
                SyntaxType::LSS, SyntaxType::LEQ, SyntaxType::GRE, SyntaxType::GEQ
        };
        genNode(curNode, SyntaxType::ADDEXP);
        while (First.count(get<0>(cursor->getNthNode(0)))) {
            parserList.emplace_back(SyntaxType::RELEXP, SyntaxType2String.at(SyntaxType::NONE));
            switch (get<0>(cursor->getNthNode(0))) {
                case SyntaxType::LSS: genNode(curNode, SyntaxType::LSS); break;
                case SyntaxType::LEQ: genNode(curNode, SyntaxType::LEQ); break;
                case SyntaxType::GRE: genNode(curNode, SyntaxType::GRE); break;
                case SyntaxType::GEQ: genNode(curNode, SyntaxType::GEQ); break;
                default: error();
            }
            genNode(curNode, SyntaxType::ADDEXP);
        }
    }

    void eqExp(Node* curNode) {
        set<SyntaxType> First = {
                SyntaxType::EQL, SyntaxType::NEQ
        };
        genNode(curNode, SyntaxType::RELEXP);
        while (First.count(get<0>(cursor->getNthNode(0)))) {
            parserList.emplace_back(SyntaxType::EQEXP, SyntaxType2String.at(SyntaxType::NONE));
            switch (get<0>(cursor->getNthNode(0))) {
                case SyntaxType::EQL: genNode(curNode, SyntaxType::EQL); break;
                case SyntaxType::NEQ: genNode(curNode, SyntaxType::NEQ); break;
                default: error();
            }
            genNode(curNode, SyntaxType::RELEXP);
        }
    }

    void lAndExp(Node* curNode) {
        genNode(curNode, SyntaxType::EQEXP);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::AND) {
            parserList.emplace_back(SyntaxType::LANDEXP, SyntaxType2String.at(SyntaxType::NONE));
            genNode(curNode, SyntaxType::AND);
            genNode(curNode, SyntaxType::EQEXP);
        }
    }

    void lOrExp(Node* curNode) {
        genNode(curNode, SyntaxType::LANDEXP);
        while (get<0>(cursor->getNthNode(0)) == SyntaxType::OR) {
            parserList.emplace_back(SyntaxType::LOREXP, SyntaxType2String.at(SyntaxType::NONE));
            genNode(curNode, SyntaxType::OR);
            genNode(curNode, SyntaxType::LANDEXP);
        }
    }

    void intConst(Node* curNode) {
        curNode->insertList(&parserList, get<1>(cursor->getNthNode(0)));
    }

    void ident(Node* curNode) {
        curNode->insertList(&parserList, get<1>(cursor->getNthNode(0)));
    }

    void formatString(Node* curNode) {
        curNode->insertList(&parserList, get<1>(cursor->getNthNode(0)));
    }

    void genNode(Node* curNode, SyntaxType type) {
        Node* node;
        switch (type) {
            case SyntaxType::COMPUNIT: compUnit(curNode); return;

            case SyntaxType::ADDCONSTEXP: node = new AddConstExpNode, addConstExp(node); break;
            case SyntaxType::ADDEXP: node = new AddExpNode, addExp(node); break;
            case SyntaxType::BLOCKITEM: node = new BlockItemNode, blockItem(node); break;
            case SyntaxType::BLOCK: node = new BlockNode, block(node); break;
            case SyntaxType::BTYPE: node = new BTypeNode, bType(node); break;
            case SyntaxType::COND: node = new CondNode, cond(node); break;
            case SyntaxType::CONSTDECL: node = new ConstDeclNode, constDecl(node); break;
            case SyntaxType::CONSTDEF: node = new ConstDefNode, constDef(node); break;
            case SyntaxType::CONSTEXP: node = new ConstExpNode, constExp(node); break;
            case SyntaxType::CONSTINITVAL: node = new ConstInitValNode, constInitVal(node); break;
            case SyntaxType::DECL: node = new DeclNode, decl(node); break;
            case SyntaxType::EQEXP: node = new EqExpNode, eqExp(node); break;
            case SyntaxType::EXP: node = new ExpNode, exp(node); break;
            case SyntaxType::FUNCDEF: node = new FuncDefNode, funcDef(node); break;
            case SyntaxType::FUNCFPARAM: node = new FuncFParamNode, funcFParam(node); break;
            case SyntaxType::FUNCFPARAMS: node = new FuncFParamsNode, funcFParams(node); break;
            case SyntaxType::FUNCRPARAMS: node = new FuncRParamsNode, funcRParams(node); break;
            case SyntaxType::FUNCTYPE: node = new FuncTypeNode, funcType(node); break;
            case SyntaxType::INITVAL: node = new InitValNode, initVal(node); break;
            case SyntaxType::INTCONST: node = new IntConstNode, intConst(node); break;
            case SyntaxType::LANDEXP: node = new LAndExpNode, lAndExp(node); break;
            case SyntaxType::LOREXP: node = new LOrExpNode, lOrExp(node); break;
            case SyntaxType::LVAL: node = new LValNode, lVal(node); break;
            case SyntaxType::MAINFUNCDEF: node = new MainFuncDefNode, mainFuncDef(node); break;
            case SyntaxType::MULEXP: node = new MulExpNode, mulExp(node); break;
            case SyntaxType::NUMBER: node = new NumberNode, number(node); break;
            case SyntaxType::PRIMARYEXP: node = new PrimaryExpNode, primaryExp(node); break;
            case SyntaxType::RELEXP: node = new RelExpNode, relExp(node); break;
            case SyntaxType::STMT: node = new StmtNode, stmt(node); break;
            case SyntaxType::UNARYEXP: node = new UnaryExpNode, unaryExp(node); break;
            case SyntaxType::UNARYOP: node = new UnaryOpNode, unaryOp(node); break;
            case SyntaxType::VARDECL: node = new VarDeclNode, varDecl(node); break;
            case SyntaxType::VARDEF: node = new VarDefNode, varDef(node); break;

            case SyntaxType::AND: node = new AndNode, cursor->next(); break;
            case SyntaxType::ASSIGN: node = new AssignNode, cursor->next(); break;
            case SyntaxType::BREAKTK: node = new BreakNode, cursor->next(); break;
            case SyntaxType::COMMA: node = new CommaNode, cursor->next();break;
            case SyntaxType::CONSTTK: node = new ConstNode, cursor->next(); break;
            case SyntaxType::CONTINUETK: node = new ContinueNode, cursor->next(); break;
            case SyntaxType::DIV: node = new DivNode, cursor->next(); break;
            case SyntaxType::ELSETK: node = new ElseNode, cursor->next(); break;
            case SyntaxType::EQL: node = new EqlNode, cursor->next(); break;
            case SyntaxType::GEQ: node = new GeqNode, cursor->next(); break;
            case SyntaxType::GETINTTK: node = new GetintNode, cursor->next(); break;
            case SyntaxType::GRE: node = new GreNode, cursor->next(); break;
            case SyntaxType::IFTK: node = new IfNode, cursor->next(); break;

            case SyntaxType::INTTK: node = new IntNode, cursor->next(); break;
            case SyntaxType::LBRACE: node = new LBraceNode, cursor->next(); break;
            case SyntaxType::LBRACK: node = new LBrackNode, cursor->next(); break;
            case SyntaxType::LEQ: node = new LeqNode, cursor->next(); break;
            case SyntaxType::LPARENT: node = new LParentNode, cursor->next(); break;
            case SyntaxType::LSS: node = new LssNode, cursor->next(); break;
            case SyntaxType::MAINTK: node = new MainNode, cursor->next(); break;
            case SyntaxType::MINU: node = new MinuNode, cursor->next(); break;
            case SyntaxType::MOD: node = new ModNode, cursor->next(); break;
            case SyntaxType::MULT: node = new MultNode, cursor->next(); break;
            case SyntaxType::NEQ: node = new NeqNode, cursor->next(); break;
            case SyntaxType::NOT: node = new NotNode, cursor->next(); break;
            case SyntaxType::OR: node = new OrNode, cursor->next(); break;
            case SyntaxType::PLUS: node = new PlusNode, cursor->next(); break;
            case SyntaxType::PRINTFTK: node = new PrintfNode, cursor->next(); break;
            case SyntaxType::RBRACE: node = new RBraceNode, cursor->next(); break;
            case SyntaxType::RBRACK: node = new RBrackNode, cursor->next(); break;
            case SyntaxType::RETURNTK: node = new ReturnNode, cursor->next(); break;
            case SyntaxType::RPARENT: node = new RParentNode, cursor->next(); break;
            case SyntaxType::SEMICN: node = new SemicnNode, cursor->next(); break;
            case SyntaxType::VOIDTK: node = new VoidNode, cursor->next(); break;
            case SyntaxType::WHILETK: node = new WhileNode, cursor->next(); break;

            case SyntaxType::IDENFR: node = new IdentNode, ident(node), cursor->next(); return;
            case SyntaxType::STRCON: node = new StrConNode, formatString(node), cursor->next(); return;
            case SyntaxType::INTCON: node = new IntConNode, intConst(node), cursor->next(); return;
            default: error(); return;
        }
        curNode->insertNodes(node);
        node->insertList(&parserList);
    }

    set<SyntaxType> StmtFirst = {
            SyntaxType::IDENFR, SyntaxType::SEMICN, SyntaxType::LBRACE, SyntaxType::IFTK, SyntaxType::WHILETK, SyntaxType::CONTINUETK,
            SyntaxType::BREAKTK, SyntaxType::RETURNTK, SyntaxType::PRINTFTK, SyntaxType::LPARENT, SyntaxType::PLUS,
            SyntaxType::MINU, SyntaxType::NOT, SyntaxType::INTCON
    };

    set<SyntaxType> ExpFirst = {
            SyntaxType::IDENFR, SyntaxType::PLUS, SyntaxType::MINU, SyntaxType::NOT, SyntaxType::LPARENT, SyntaxType::INTCON
    };

    void fileWrite(const char *outputFile) {
        ofstream f(outputFile);
        for (auto i : parserList) {
            if (std::get<1>(i) == SyntaxType2String.at(SyntaxType::NONE)) {
                f << "<" << SyntaxType2String.at(std::get<0>(i)) << ">" << "\n";
            } else {
                f << SyntaxType2String.at(std::get<0>(i)) << " " << std::get<1>(i) << "\n";
            }
        }
    }

    void error() {
        cout << "error!" << "\n";
    }

public:
    explicit Parser(vector<tuple<SyntaxType, string>> lexerList, const char* outputFile) {
        cursor = new ParseCursor(move(lexerList));
        Node* root = new CompUnitNode;
        syntaxTree = new SyntaxTree(root);
        genNode(root, SyntaxType::COMPUNIT);
        fileWrite(outputFile);
    }
};
#endif //TAYILER_PARSER_H