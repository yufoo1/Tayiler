//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_VISITOR_H
#define TAYILER_VISITOR_H

#include <utility>

#include "../node/Node.h"
#include "../Manager/Manager.h"
#include "llvm-ir/instr/StoreInstr.h"
#include "llvm-ir/constant/ConstantInt.h"
#include "llvm-ir/instr/AllocaInstr.h"
#include "llvm-ir/instr/GetintInstr.h"
#include "llvm-ir/instr/GetElementPtrInstr.h"
#include "llvm-ir/instr/PutstrInstr.h"
#include "llvm-ir/instr/PutintInstr.h"
#include "llvm-ir/instr/CallInstr.h"
#include "llvm-ir/global-val/GlobalInt.h"
#include "llvm-ir/instr/IcmpInstr.h"
#include "llvm-ir/instr/BrInstr.h"

class Visitor {

private:
    Manager* manager = nullptr;
    BasicBlock* curBasicBlock = nullptr;
    BasicBlock* globalBasicBlock = nullptr;
    SymbolTable* curSymbolTable = nullptr;
    SymbolTable* globalSymbolTable = nullptr;
    Function* globalFunction = nullptr;
    Function* curFunction = nullptr;
    vector<tuple<int, string>> errorList;

    void visitAst(Node* root) {
        visitCompUnit(dynamic_cast<CompUnitNode *>(root));
    }

    bool checkSymbolTable(const string& ident) {
        SymbolTable* cur = curSymbolTable;
        while(cur != nullptr) {
            if(cur->getSymbolTerms()->count(ident)) {
                return true;
            }
            cur = cur->getParent();
        }
        return false;
    }

    SymbolTerm* getSymbolTermIteratively(const string& ident) {
        SymbolTable* cur = curSymbolTable;
        while(cur != nullptr) {
            if(cur->getSymbolTerms()->count(ident)) {
                return cur->getSymbolTerm(ident);
            }
            cur = cur->getParent();
        }
        return nullptr;
    }

    void visitCompUnit(CompUnitNode* node) {
        for (auto i : (node->getDeclVec())) visitDecl(dynamic_cast<DeclNode *>(i), true);
        for (auto i : (node->getFuncDefVec())) visitFuncDef(dynamic_cast<FuncDefNode *>(i));
        visitMainFuncDef(node->getMainFuncDef());
    }

    void visitFuncDef(FuncDefNode* node) {
        if(manager->getFunctions().count(node->getIdent()->getVal()) || checkSymbolTable(node->getIdent()->getVal())) {
            errorList.emplace_back(node->getIdent()->getLine(), "b");
        }
        auto* entry = new BasicBlock();
        curBasicBlock = entry;
        curSymbolTable = new SymbolTable(globalSymbolTable);
        auto *params = new vector<Param*>;
        if (node->getFunFParams() != nullptr) {
            for (auto i : node->getFunFParams()->getFuncFParams()) {
                auto* param = new Param(dynamic_cast<FuncFParamNode*>(i)->getIdent()->getVal(), SyntaxType2FuncType.at(dynamic_cast<FuncFParamNode*>(i)->getBType()->getChild()->getType()), dynamic_cast<FuncFParamNode*>(i)->getDimensionality(), dynamic_cast<FuncFParamNode*>(i)->getIdent()->getLine());
                params->emplace_back(param);
            }
        }
        auto retParam = new Param("", SyntaxType2FuncType.at(node->getFuncType()->getTokenType()), -1);
        auto* function = new Function(entry, curSymbolTable, node->getIdent()->getVal(), params, retParam, SyntaxType2FuncType.at(node->getFuncType()->getTokenType()));
        curFunction = function;
        manager->addFunction(function);
        for (auto i : *params) {
            if(curSymbolTable->getSymbolTerms()->count(i->getIdent())) {
                errorList.emplace_back(i->getIdentLine(), "b");
            } else {
                auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, i->getIdent(), i->getFuncType(), false, true, curFunction->genInstrIdx());
                curSymbolTable->addSymbolTerm(new SymbolTerm(i->getIdent(), i->getFuncType(), false, i->getDimensionality(), allocInstr));
                i->setVal(allocInstr->getVal());
            }
        }
        auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, retParam->getIdent(), retParam->getFuncType(), false, true, curFunction->genInstrIdx());
        curSymbolTable->addSymbolTerm(new SymbolTerm(retParam->getIdent(), retParam->getFuncType(), false, retParam->getDimensionality(), allocInstr));
        visitBlock(node->getBlock());
        curSymbolTable = curSymbolTable->getParent();
    }

    void visitMainFuncDef(MainFuncDefNode* node) {
        FuncType retType = FuncType::INT32;
        auto* entry = new BasicBlock();
        string ident = ReservedWordMapReversed.at(SyntaxType::MAINTK);
        curBasicBlock = entry;
        curSymbolTable = new SymbolTable(globalSymbolTable);
        auto* function = new Function(curBasicBlock, curSymbolTable, ident, nullptr, nullptr, retType);
        manager->setMainFunction(function);
        curFunction = function;
        visitBlock(node->getBlock());
        curSymbolTable = curSymbolTable->getParent();
        curBasicBlock = nullptr, curFunction = nullptr;
    }

    void visitBlock(BlockNode* node) {
        YASSERT(curBasicBlock != nullptr);
        for (auto i : node->getBlockItems()) {
            visitBlockItem(dynamic_cast<BlockItemNode *>(i));
        }
    }

    void visitBlockItem(BlockItemNode* node) {
        switch (node->getChild()->getType()) {
            case SyntaxType::STMT: visitStmt(dynamic_cast<StmtNode *>(node->getChild())); break;
            case SyntaxType::DECL: visitDecl(dynamic_cast<DeclNode *>(node->getChild()), false); break;
            default: error();
        }
    }

    void visitStmt(StmtNode* node) {
        switch (node->getStmtType()) {
            case StmtType::BLOCK: {
                curSymbolTable = new SymbolTable(curSymbolTable);
                visitBlockStmt(node);
                curSymbolTable = curSymbolTable->getParent();
                break;
            }
            case StmtType::BREAK: visitBreakStmt(node); break;
            case StmtType::CONTINUE: visitContinueStmt(node); break;
            case StmtType::EXP: visitExpStmt(node); break;
            case StmtType::GETINT: visitGetintStmt(node); break;
            case StmtType::IF: visitIfStmt(node); break;
            case StmtType::LVALASSIGN: visitLValAssignStmt(node); break;
            case StmtType::PRINTF: visitPrintfStmt(node); break;
            case StmtType::RETURN: visitReturnStmt(node); break;
            case StmtType::WHILE: visitWhileStmt(node); break;
            case StmtType::SEMICN: visitSemicnStmt(node); break;
            default: error(); break;
        }
    }

    void visitBlockStmt(StmtNode* node) {
        visitBlock(node->getBlock());
    }

    void visitBreakStmt(StmtNode* node) {

    }

    void visitContinueStmt(StmtNode* node) {

    }

    Value* visitExpStmt(StmtNode* node) {
        return visitExp(node->getExps().front());
    }

    void visitGetintStmt(StmtNode* node) {
        if(!checkSymbolTable(node->getLVal()->getIdent()->getVal())) {
            errorList.emplace_back(node->getLVal()->getIdent()->getLine(), "c");
        } else if(getSymbolTermIteratively(node->getLVal()->getIdent()->getVal())->getIsConstant()) {
            errorList.emplace_back(node->getLVal()->getIdent()->getLine(), "h");
        } else {
            new GetintInstr(curBasicBlock, visitLVal(node->getLVal()));
        }
    }

    Value* visitLVal(LValNode* node) {
        if(!checkSymbolTable(node->getIdent()->getVal())) {
            errorList.emplace_back(node->getIdent()->getLine(), "c"); return nullptr;
        } else {
            for(auto i : node->getExps()) {
                visitExp(dynamic_cast<ExpNode*>(i));
            }
            return getSymbolTermIteratively(node->getIdent()->getVal())->getAllocaInstr();
        }
    }

    void visitIfStmt(StmtNode* node) {
        auto* condBasicBlock = new BasicBlock();
        auto* ifBasicBlock = new BasicBlock();
        auto* endBasicBlock = new BasicBlock();
        curFunction->addBasicBlock(condBasicBlock);
        curFunction->addBasicBlock(ifBasicBlock);
        curFunction->addBasicBlock(endBasicBlock);
        curBasicBlock = condBasicBlock;
        Value* icmp = visitCond(node->getCond());
        if(node->getStmts().size() == 1) {
            new BrInstr(curBasicBlock, icmp, ifBasicBlock, endBasicBlock);
            curBasicBlock = ifBasicBlock;
            visitStmt(node->getStmts().front());
        } else {
            YASSERT(node->getStmts().size() == 2)
            auto* elseBasicBlock = new BasicBlock();
            curFunction->addBasicBlock(elseBasicBlock);
            new BrInstr(curBasicBlock, icmp, ifBasicBlock, elseBasicBlock);
            curBasicBlock = ifBasicBlock;
            visitStmt(node->getStmts().front());
            new BrInstr(curBasicBlock, endBasicBlock);
            curBasicBlock = elseBasicBlock;
            visitStmt(node->getStmts().back());
        }
        new BrInstr(curBasicBlock, endBasicBlock);
        curBasicBlock = endBasicBlock;
    }

    Value* visitCond(CondNode* node) {
        return visitLOrExp(dynamic_cast<LOrExpNode*>(node->getChild()));
    }

    Value* visitLOrExp(LOrExpNode* node) {
        if(node->getLAndExps().size() == 1) {
            return visitLAndExp(dynamic_cast<LAndExpNode *>(node->getLAndExps().front()));
        } else {

        }
    }

    Value* visitLAndExp(LAndExpNode* node) {
        if(node->getEqExps().size() == 1) {
            return visitEqExp(dynamic_cast<EqExpNode *>(node->getEqExps().front()));
        } else {

        }
    }

    Value* visitEqExp(EqExpNode* node) {
        if(node->getRelExps().size() == 1) {
            return visitRelExp(dynamic_cast<RelExpNode *>(node->getRelExps().front()));
        } else {

        }
    }

    Value* visitRelExp(RelExpNode* node) {
        if(node->getAddExps().size() == 1) {
            return new IcmpInstr(curBasicBlock, visitAddExp(dynamic_cast<AddExpNode *>(node->getAddExps().front())), CONSTANT_ZERO, SyntaxType::NEQ, curFunction->genInstrIdx());
        } else {

        }
    }

    void visitLValAssignStmt(StmtNode* node) {
        /* TODO array */
        if(!checkSymbolTable(node->getLVal()->getIdent()->getVal())) {
            errorList.emplace_back(node->getLVal()->getIdent()->getLine(), "c");
        } else if(getSymbolTermIteratively(node->getLVal()->getIdent()->getVal())->getIsConstant()) {
            errorList.emplace_back(node->getLVal()->getIdent()->getLine(), "h");
        } else {
            new StoreInstr(curBasicBlock, visitLVal(node->getLVal()), visitExp(node->getExps().front()));
        }
    }

    void visitPrintfStmt(StmtNode* node) {
        string formatString = node->getFormatString();
        vector<ExpNode*> exps = node->getExps();
        int i = 0, cnt = 0;
        string str;
        while (i < formatString.length()) {
            if (formatString.at(i) != '\"' && formatString.at(i) != '%') {
                str += formatString.at(i);
            } else if (formatString.at(i) == '\"' && !str.empty() || formatString.at(i) == '%') {
                if (!str.empty()) {
                    auto* globalString = new GlobalString(str);
                    GLOBALSTRINGS.insert(globalString);
                    auto* instr = new GetElementPtrInstr(curBasicBlock, globalString, curFunction->genInstrIdx());
                    new PutstrInstr(curBasicBlock, instr);
                }
                if (formatString.at(i) == '%') {
                    if (formatString.at(++i) == 'd') {
                        if(cnt < exps.size()) {
                            new PutintInstr(curBasicBlock, visitExp(exps.at(cnt++)));
                        }
                    } else {
                        error();
                    }
                }
                str.clear();
            }
            ++i;
        }
    }

    void visitReturnStmt(StmtNode* node) {
        new ReturnInstr(curBasicBlock, node->getExps().empty() ? nullptr : visitExp(node->getExps().front()),
                        curFunction->getIdent() == ReservedWordMapReversed.at(SyntaxType::MAINTK) ? nullptr : curFunction->getSymbolTable()->getSymbolTerms()->at("")->getAllocaInstr(),
                        curFunction->getIdent() == ReservedWordMapReversed.at(SyntaxType::MAINTK));
    }

    void visitWhileStmt(StmtNode* node) {
        auto* condBasicBlock = new BasicBlock();
        auto* whileBasicBlock = new BasicBlock();
        auto* endBasicBlock = new BasicBlock();
        curFunction->addBasicBlock(condBasicBlock);
        curFunction->addBasicBlock(whileBasicBlock);
        curFunction->addBasicBlock(endBasicBlock);
        curBasicBlock = condBasicBlock;
        Value* icmp = visitCond(node->getCond());
        new BrInstr(curBasicBlock, icmp, whileBasicBlock, endBasicBlock);
        curBasicBlock = whileBasicBlock;
        visitStmt(node->getStmts().front());
        new BrInstr(curBasicBlock, condBasicBlock);
        curBasicBlock = endBasicBlock;
    }

    void visitSemicnStmt(StmtNode* node) {

    }

    void visitDecl(DeclNode* node, bool isGlobal) {
        switch (node->getChild()->getType()) {
            case SyntaxType::CONSTDECL: visitConstDecl(dynamic_cast<ConstDeclNode *>(node->getChild()), true, isGlobal); break;
            case SyntaxType::VARDECL: visitVarDecl(dynamic_cast<VarDeclNode *>(node->getChild()), false, isGlobal); break;
            default: error(); break;
        }
    }

    void visitConstDecl(ConstDeclNode* node, bool isConstant, bool isGlobal) {
        FuncType type = SyntaxType2FuncType.at(node->getBType()->getChild()->getType());
        vector<Node*> constDefs = node->getConstDefs();
        for (auto i : constDefs) visitConstDef(dynamic_cast<ConstDefNode *>(i), type, isConstant, isGlobal);
    }

    void visitConstDef(ConstDefNode* node, FuncType type, bool isConstant, bool isGlobal) {
        /* TODO: without array */
        if (isGlobal) {
            if(manager->getFunctions().count(node->getIdent()->getVal()) || curSymbolTable->getSymbolTerms()->count(node->getIdent()->getVal())) {
                errorList.emplace_back(node->getIdent()->getLine(), "b");
            } else {
                auto* allocaInstr = new AllocaInstr(globalBasicBlock, globalSymbolTable, node->getIdent()->getVal(), type, isConstant, true, 0);
                globalSymbolTable->addSymbolTerm(new SymbolTerm(node->getIdent()->getVal(), type, isConstant, node->getConstExps().size(), allocaInstr));
                new StoreInstr(globalBasicBlock, allocaInstr, visitConstInitVal(node->getConstInitVal()));
                GLOBALINTS.insert(new GlobalInt(allocaInstr));
            }
        } else {
            if(curSymbolTable->getSymbolTerms()->count(node->getIdent()->getVal())) {
                errorList.emplace_back(node->getIdent()->getLine(), "b");
            } else {
                auto* allocaInstr = new AllocaInstr(curBasicBlock, curSymbolTable, node->getIdent()->getVal(), type, isConstant, false, curFunction->genInstrIdx());
                curSymbolTable->addSymbolTerm(new SymbolTerm(node->getIdent()->getVal(), type, isConstant, node->getConstExps().size(), allocaInstr));
                new StoreInstr(curBasicBlock, allocaInstr, visitConstInitVal(node->getConstInitVal()));
            }
        }
    }

    Value* visitConstInitVal(ConstInitValNode* node) {
        if (node->getConstExp() != nullptr) {
            return visitConstExp(node->getConstExp());
        } else {
            /* TODO {InitVal{...}}*/
            error(); return nullptr;
        }
    }

    Value* visitConstExp(ConstExpNode* node) {
        return visitAddExp(dynamic_cast<AddExpNode *>(node->getChild()));
    }

    void visitVarDecl(VarDeclNode* node, bool isConstant, bool isGlobal) {
        FuncType type = SyntaxType2FuncType.at(node->getBType()->getChild()->getType());
        vector<Node*> varDefs = node->getVarDefs();
        for (auto i : varDefs) visitVarDef(dynamic_cast<VarDefNode *>(i), type, isConstant, isGlobal);
    }

    void visitVarDef(VarDefNode* node, FuncType type, bool isConstant, bool isGlobal) {
        /* TODO: without array */
        if (isGlobal) {
            if(manager->getFunctions().count(node->getIdent()->getVal()) || curSymbolTable->getSymbolTerms()->count(node->getIdent()->getVal())) {
                errorList.emplace_back(node->getIdent()->getLine(), "b");
            } else {
                auto* allocaInstr = new AllocaInstr(globalBasicBlock, globalSymbolTable, node->getIdent()->getVal(), type, isConstant, true, 0);
                globalSymbolTable->addSymbolTerm(new SymbolTerm(node->getIdent()->getVal(), type, isConstant, node->getConstExps().size(), allocaInstr));
                if (node->getInitVal() != nullptr) {
                    new StoreInstr(globalBasicBlock, allocaInstr, visitInitVal(node->getInitVal()));
                }
                GLOBALINTS.insert(new GlobalInt(allocaInstr));
            }
        } else {
            if(curSymbolTable->getSymbolTerms()->count(node->getIdent()->getVal())) {
                errorList.emplace_back(node->getIdent()->getLine(), "b");
            } else {
                auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, node->getIdent()->getVal(), type, isConstant, false, curFunction->genInstrIdx());
                curSymbolTable->addSymbolTerm(new SymbolTerm(node->getIdent()->getVal(), type, isConstant, node->getConstExps().size(), allocInstr));
                if (node->getInitVal() != nullptr) {
                    new StoreInstr(curBasicBlock, allocInstr, visitInitVal(node->getInitVal()));
                }
            }
        }
    }

    Value* visitInitVal(InitValNode* node) {
        if (node->getExp() != nullptr) {
            return visitExp(node->getExp());
        } else {
            /* TODO {InitVal{...}}*/
            error(); return nullptr;
        }
    }

    Value* visitExp(ExpNode* node) {
        return visitAddExp(dynamic_cast<AddExpNode *>(node->getChild()));
    }

    Value* visitAddExp(AddExpNode* node) {
        if (node->getMulExps().size() == 1) {
            return visitMulExp(dynamic_cast<MulExpNode *>(node->getMulExps().front()));
        } else {
            vector<Node*> mulExps = node->getMulExps();
            vector<SyntaxType> ops = node->getOps();
            Value* mulExp = visitMulExp(dynamic_cast<MulExpNode *>(mulExps.front()));
            YASSERT(mulExps.size() - 1 == ops.size());
            for (int i = 0; i < ops.size(); i++) {
                mulExp = new AluInstr(curBasicBlock == nullptr ? globalBasicBlock : curBasicBlock, mulExp, visitMulExp(dynamic_cast<MulExpNode *>(mulExps.at(i + 1))), ops.at(i), curFunction->genInstrIdx());
            }
            return mulExp;
        }

    }

    Value* visitMulExp(MulExpNode* node) {
        if (node->getUnaryExps().size() == 1) {
            return visitUnaryExp(dynamic_cast<UnaryExpNode *>(node->getUnaryExps().front()));
        } else {
            vector<Node*> unaryExps = node->getUnaryExps();
            vector<SyntaxType> ops = node->getOps();
            Value* unaryExp = visitUnaryExp(dynamic_cast<UnaryExpNode *>(unaryExps.front()));
            YASSERT(unaryExps.size() - 1 == ops.size());
            for (int i = 0; i < ops.size(); i++) {
                unaryExp = new AluInstr(curBasicBlock == nullptr ? globalBasicBlock : curBasicBlock, unaryExp, visitUnaryExp(dynamic_cast<UnaryExpNode *>(unaryExps.at(i + 1))), ops.at(i), curFunction->genInstrIdx());
            }
            return unaryExp;
        }
    }

    Value* visitUnaryExp(UnaryExpNode* node) {
        if (node->getPrimaryExp() != nullptr) {
            return visitPrimaryExp(node->getPrimaryExp());
        } else if (node->getIdent() != nullptr) {
            if(!manager->hasFunction(node->getIdent()->getVal())) {
                errorList.emplace_back(node->getIdent()->getLine(), "c");
            } else {
                if((node->getFuncRParams() == nullptr ? 0 : node->getFuncRParams()->getExps().size()) !=  manager->getFunction(node->getIdent()->getVal())->getParams()->size()) {
                    errorList.emplace_back(node->getIdent()->getLine(), "d");
                } else {
                    vector<Value *>* values = new vector<Value*>;
                    if (node->getFuncRParams() != nullptr) {
                        vector<Node*> exps = node->getFuncRParams()->getExps();
                        for(int i = 0; i < exps.size(); ++i) {
                            Value* exp = visitExp(dynamic_cast<ExpNode *>(exps.at(i)));
                            if(exp != nullptr) {
                                if(exp->getFuncType() != manager->getFunction(node->getIdent()->getVal())->getParams()->at(i)->getFuncType() || getDimensionality(dynamic_cast<ExpNode *>(exps.at(i))) != manager->getFunction(node->getIdent()->getVal())->getParams()->at(i)->getDimensionality()) {
                                    errorList.emplace_back(node->getIdent()->getLine(), "e");
                                } else {
                                    values->emplace_back(visitExp(dynamic_cast<ExpNode *>(exps.at(i))));
                                }
                            }
                        }
                    }
                    vector<AllocaInstr *> *allocaInstrs = new vector<AllocaInstr*>;
                    for (auto i: *manager->getFunction(node->getIdent()->getVal())->getParams()) {
                        allocaInstrs->emplace_back(dynamic_cast<AllocaInstr *>
                                                   (manager->getFunction(node->getIdent()->getVal())->getSymbolTable()->getSymbolTerm(i->getIdent())->getAllocaInstr()));
                    }
                    new CallInstr(curBasicBlock, manager->getFunction(node->getIdent()->getVal()), values, allocaInstrs);
                    return manager->getFunction(node->getIdent()->getVal())->getSymbolTable()->getSymbolTerm("")->getAllocaInstr();
                }
            }
        } else if (node->getUnaryOp() != SyntaxType::NONE) {
            Value* unaryExp = visitUnaryExp(node->getUnaryExp());
            unaryExp->setFuncType(FuncType::INT32);
            switch (node->getUnaryOp()) {
                case SyntaxType::MINU:
                    unaryExp = new AluInstr(curBasicBlock == nullptr ? globalBasicBlock : curBasicBlock, CONSTANT_ZERO, unaryExp, node->getUnaryOp(), curFunction->genInstrIdx());
                    break;
                default: break;
            }
            return unaryExp;
        } else {
            error(); return nullptr;
        }
        error(); return nullptr;
    }

    int getDimensionality(ExpNode* node) {
        AddExpNode* addExp = dynamic_cast<AddExpNode *>(node->getChild());
        if (addExp->getMulExps().size() == 1) {
            MulExpNode* mulExp = dynamic_cast<MulExpNode *>(addExp->getMulExps().front());
            if (mulExp->getUnaryExps().size() == 1) {
                UnaryExpNode* unaryExp = dynamic_cast<UnaryExpNode *>(mulExp->getUnaryExps().front());
                if (unaryExp->getPrimaryExp() != nullptr) {
                    PrimaryExpNode* primaryExp = unaryExp->getPrimaryExp();
                    if (primaryExp->getLVal() != nullptr) {
                        LValNode* lVal = primaryExp->getLVal();
                        if(!checkSymbolTable(lVal->getIdent()->getVal())) {
                            errorList.emplace_back(lVal->getIdent()->getLine(), "c"); return 0;
                        } else {
                            return getSymbolTermIteratively(lVal->getIdent()->getVal())->getDimensionality() - lVal->getExps().size();
                        }
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    Value* visitPrimaryExp(PrimaryExpNode* node) {
        if (node->getExp() != nullptr) {
            return visitExp(node->getExp());
        } else if (node->getLVal() != nullptr) {
            return visitLVal(node->getLVal());
        } else if (node->getNumber() != nullptr) {
            return visitNumber(node->getNumber());
        } else {
            error(); return nullptr;
        }
    }

    Value* visitNumber(NumberNode* node) {
        ConstantInt* constantInt = new ConstantInt(node->getChild()->getVal());
        AluInstr* aluInstr = new AluInstr(curBasicBlock == nullptr ? globalBasicBlock : curBasicBlock, CONSTANT_ZERO, constantInt, SyntaxType::PLUS, curFunction == nullptr ? 0 : curFunction->genInstrIdx());
        return aluInstr;
    }

    void error() {
        cout << "error!" << endl;
    }

public:
    explicit Visitor(Node* root, vector<tuple<int, string>> errorList) {
        this->errorList = std::move(errorList);
        manager = new Manager(&this->errorList);
        globalSymbolTable = new SymbolTable(nullptr);
        globalBasicBlock = new BasicBlock();
        globalFunction = new Function(globalBasicBlock, globalSymbolTable, "", nullptr, nullptr, FuncType::VOID);
        manager->setGlobalBasicBlock(globalBasicBlock);
        curFunction = globalFunction;
        curSymbolTable = globalSymbolTable;
        visitAst(root);
    }
    Manager* getManager() {
        return manager;
    }
};
#endif //TAYILER_VISITOR_H
