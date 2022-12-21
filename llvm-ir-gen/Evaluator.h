//
// Created by yufoo1 on 2022/12/13.
//

#ifndef TAYILER_EVALUATOR_H
#define TAYILER_EVALUATOR_H

#include "symbol/SymbolTable.h"
#include "../node/nonterminal/ConstExpNode.h"

class Evaluator {
private:
    SymbolTable* symbolTable = nullptr;
public:
    explicit Evaluator(SymbolTable* symbolTable) {
        this->symbolTable = symbolTable;
    }

    int evalConstExp(ConstExpNode* node) {
        return evalAddExp(dynamic_cast<AddExpNode *>(node->getChild()));
    }
private:
    int evalExp(ExpNode* node) {
        return evalAddExp(dynamic_cast<AddExpNode *>(node->getChild()));
    }

    int evalAddExp(AddExpNode* node) {
        int val = 0;
        for(int i = 0; i < node->getMulExps().size(); ++i) {
            if(i == 0) {
                val += evalMulExp(dynamic_cast<MulExpNode*>(node->getMulExps().at(i)));
            } else {
                switch (node->getOps().at(i - 1)) {
                    case SyntaxType::PLUS: val += evalMulExp(dynamic_cast<MulExpNode*>(node->getMulExps().at(i))); break;
                    case SyntaxType::MINU: val -= evalMulExp(dynamic_cast<MulExpNode*>(node->getMulExps().at(i))); break;
                    default: break;
                }
            }
        }
        return val;
    }

    int evalMulExp(MulExpNode* node) {
        int val = 0;
        for(int i = 0; i < node->getUnaryExps().size(); ++i) {
            if(i == 0) {
                val += evalUnaryExp(dynamic_cast<UnaryExpNode*>(node->getUnaryExps().at(i)));
            } else {
                switch (node->getOps().at(i - 1)) {
                    case SyntaxType::MULT: val *= evalUnaryExp(dynamic_cast<UnaryExpNode*>(node->getUnaryExps().at(i))); break;
                    case SyntaxType::DIV: val /= evalUnaryExp(dynamic_cast<UnaryExpNode*>(node->getUnaryExps().at(i))); break;
                    case SyntaxType::MOD: val %= evalUnaryExp(dynamic_cast<UnaryExpNode*>(node->getUnaryExps().at(i))); break;
                    default: break;
                }
            }
        }
        return val;
    }

    int evalUnaryExp(UnaryExpNode* node) {
        if(node->getPrimaryExp() != nullptr) {
            return evalPrimaryExp(node->getPrimaryExp());
        } else if(node->getIdent() != nullptr) {

        } else if(node->getUnaryOp() != SyntaxType::NONE) {
            switch (node->getUnaryOp()) {
                case SyntaxType::PLUS: return evalUnaryExp(node->getUnaryExp()); break;
                case SyntaxType::MINU: return -1 * evalUnaryExp(node->getUnaryExp()); break;
                default: break;
            }
        } else {
            error(); return 0;
        }
    }

    int evalPrimaryExp(PrimaryExpNode* node) {
        if(node->getExp() != nullptr) {
            return evalExp(node->getExp());
        } else if(node->getLVal() != nullptr) {
            return evalLVal(node->getLVal());
        } else if(node->getNumber()) {
            return evalNumber(node->getNumber());
        } else {
            error(); return 0;
        }
    }

    int evalLVal(LValNode* node) {

    }

    int evalNumber(NumberNode* node) {
        return evalIntCon(dynamic_cast<IntConNode *>(node->getChild()));
    }

    int evalIntCon(IntConNode* node) {
        return std::stoi(node->getVal());
    }

    void error() {
        cout << "Evaluator error!";
    }
};
#endif //TAYILER_EVALUATOR_H
