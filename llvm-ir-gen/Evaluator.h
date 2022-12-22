//
// Created by yufoo1 on 2022/12/13.
//

#ifndef TAYILER_EVALUATOR_H
#define TAYILER_EVALUATOR_H

#include "symbol/SymbolTable.h"
#include "../node/nonterminal/ConstExpNode.h"

class Evaluator {
public:
    explicit Evaluator() = default;

    int evalConstExp(ConstExpNode* node, SymbolTable* curSymbolTable) {
        return evalAddExp(dynamic_cast<AddExpNode *>(node->getChild()), curSymbolTable);
    }
private:
    int evalExp(ExpNode* node, SymbolTable* curSymbolTable) {
        return evalAddExp(dynamic_cast<AddExpNode *>(node->getChild()), curSymbolTable);
    }

    int evalAddExp(AddExpNode* node, SymbolTable* curSymbolTable) {
        int val = 0;
        for(int i = 0; i < node->getMulExps().size(); ++i) {
            if(i == 0) {
                val += evalMulExp(dynamic_cast<MulExpNode*>(node->getMulExps().at(i)), curSymbolTable);
            } else {
                switch (node->getOps().at(i - 1)) {
                    case SyntaxType::PLUS: val += evalMulExp(dynamic_cast<MulExpNode*>(node->getMulExps().at(i)), curSymbolTable); break;
                    case SyntaxType::MINU: val -= evalMulExp(dynamic_cast<MulExpNode*>(node->getMulExps().at(i)), curSymbolTable); break;
                    default: break;
                }
            }
        }
        return val;
    }

    int evalMulExp(MulExpNode* node, SymbolTable* curSymbolTable) {
        int val = 0;
        for(int i = 0; i < node->getUnaryExps().size(); ++i) {
            if(i == 0) {
                val += evalUnaryExp(dynamic_cast<UnaryExpNode*>(node->getUnaryExps().at(i)), curSymbolTable);
            } else {
                switch (node->getOps().at(i - 1)) {
                    case SyntaxType::MULT: val *= evalUnaryExp(dynamic_cast<UnaryExpNode*>(node->getUnaryExps().at(i)), curSymbolTable); break;
                    case SyntaxType::DIV: val /= evalUnaryExp(dynamic_cast<UnaryExpNode*>(node->getUnaryExps().at(i)), curSymbolTable); break;
                    case SyntaxType::MOD: val %= evalUnaryExp(dynamic_cast<UnaryExpNode*>(node->getUnaryExps().at(i)), curSymbolTable); break;
                    default: break;
                }
            }
        }
        return val;
    }

    int evalUnaryExp(UnaryExpNode* node, SymbolTable* curSymbolTable) {
        if(node->getPrimaryExp() != nullptr) {
            return evalPrimaryExp(node->getPrimaryExp(), curSymbolTable);
        } else if(node->getIdent() != nullptr) {

        } else if(node->getUnaryOp() != SyntaxType::NONE) {
            switch (node->getUnaryOp()) {
                case SyntaxType::PLUS: return evalUnaryExp(node->getUnaryExp(), curSymbolTable); break;
                case SyntaxType::MINU: return -1 * evalUnaryExp(node->getUnaryExp(), curSymbolTable); break;
                default: break;
            }
        } else {
            error(); return 0;
        }
    }

    int evalPrimaryExp(PrimaryExpNode* node, SymbolTable* curSymbolTable) {
        if(node->getExp() != nullptr) {
            return evalExp(node->getExp(), curSymbolTable);
        } else if(node->getLVal() != nullptr) {
            return evalLVal(node->getLVal(), curSymbolTable);
        } else if(node->getNumber()) {
            return evalNumber(node->getNumber(), curSymbolTable);
        } else {
            error(); return 0;
        }
    }

    int evalLVal(LValNode* node, SymbolTable* curSymbolTable) {
        return evalConstExp(dynamic_cast<ConstExpNode*>(curSymbolTable->getSymbolTerm(node->getIdent()->getVal())->getConstExp()), curSymbolTable);
    }

    int evalNumber(NumberNode* node, SymbolTable* curSymbolTable) {
        return evalIntCon(dynamic_cast<IntConNode *>(node->getChild()), curSymbolTable);
    }

    int evalIntCon(IntConNode* node, SymbolTable* curSymbolTable) {
        return std::stoi(node->getVal());
    }

    void error() {
        cout << "Evaluator error!";
    }
};
#endif //TAYILER_EVALUATOR_H
