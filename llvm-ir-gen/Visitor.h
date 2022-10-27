//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_VISITOR_H
#define TAYILER_VISITOR_H

#include "../node/Node.h"
#include "Manager.h"
#include "llvm-ir/BasicBlock.h"
#include "symbol/SymbolTable.h"
#include "llvm-ir/Function.h"
#include "llvm-ir/Constant.h"

class Visitor {
public:
    Visitor(Node* root) {
        manager = new Manager;
        visitAst(root);
        manager->outputLLVM("llvm.ll");
    }

private:
    Manager* manager;
    BasicBlock* curBasicBlock;
    SymbolTable* curSymbolTable;
    Function* curFunction;

    void visitAst(Node* root) {
        visitCompUnit(dynamic_cast<CompUnitNode *>(root));
    }

    void visitCompUnit(CompUnitNode* node) {
        for (auto i : (node->getDeclVec())) visitDecl(dynamic_cast<DeclNode *>(i));
        for (auto i : (node->getFuncDefVec())) visitFuncDef(dynamic_cast<FuncDefNode *>(i));
        visitMainFuncDef(node->getMainFuncDef());
    }

    void visitFuncDef(FuncDefNode* node) {

        string ident = node->getVal();
    }

    void visitMainFuncDef(MainFuncDefNode* node) {
        FuncType retType = FuncType::INT32;
        auto* entry = new BasicBlock();
        string ident = ReservedWordMapReversed.at(SyntaxType::MAINTK);
        curBasicBlock = entry;
        curSymbolTable = new SymbolTable(curSymbolTable);
        auto* function = new Function(ident, retType);
        manager->addFunction(function);
        function->setBody(entry);
        curFunction = function;
        entry->setFunction(curFunction);
        visitBlock(node->getBlock());
//        if (curBasicBlock.isTerminated()) {
//
//        }
        curSymbolTable = curSymbolTable->getParent();
        curBasicBlock = nullptr, curFunction = nullptr;
    }

    void visitBlock(BlockNode* node) {
        assert(curBasicBlock != nullptr);
        for (auto i : node->getBlockItems()) {
            visitBlockItem(dynamic_cast<BlockItemNode *>(i));
        }
    }

    void visitBlockItem(BlockItemNode* node) {
        switch (node->getChild()->getType()) {
            case SyntaxType::STMT: visitStmt(dynamic_cast<StmtNode *>(node->getChild())); break;
            case SyntaxType::DECL: visitDecl(dynamic_cast<DeclNode *>(node->getChild())); break;
            default: error();
        }
    }

    void visitStmt(StmtNode* node) {
        switch (node->getStmtType()) {
            case StmtType::BLOCK: visitBlockStmt(node); break;
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

    }

    void visitBreakStmt(StmtNode* node) {

    }

    void visitContinueStmt(StmtNode* node) {

    }

    Value visitExpStmt(StmtNode* node) {

    }

    void visitGetintStmt(StmtNode* node) {

    }

    void visitIfStmt(StmtNode* node) {

    }

    void visitLValAssignStmt(StmtNode* node) {

    }

    void visitPrintfStmt(StmtNode* node) {

    }

    void visitReturnStmt(StmtNode* node) {
        if (node->getExps().empty()) {
            new Instr::ReturnInstr(curBasicBlock);
        } else {
            new Instr::ReturnInstr(curBasicBlock, visitExp(node->getExps().front()));
        }
    }

    void visitWhileStmt(StmtNode* node) {

    }

    void visitSemicnStmt(StmtNode* node) {

    }

    void visitDecl(DeclNode* node) {

    }

    Value visitExp(ExpNode* node) {
        return visitAddExp(dynamic_cast<AddExpNode *>(node->getChild()));
    }

    Value visitAddExp(AddExpNode* node) {
        // 暂时仅支持二元
        if (node->getMulExps().size() == 1) {
            return visitMulExp(dynamic_cast<MulExpNode *>(node->getMulExps().front()));
        } else {
            Value first = visitExp(dynamic_cast<ExpNode *>(node->getMulExps().front()));
            Value second = visitExp(dynamic_cast<ExpNode *>(node->getMulExps().back()));
            SyntaxType op = node->getOps().front();
        }

    }

    Value visitMulExp(MulExpNode* node) {
        // 暂时仅支持二元
        if (node->getUnaryExps().size() == 1) {
            return visitUnaryExp(dynamic_cast<UnaryExpNode *>(node->getUnaryExps().front()));
        } else {

        }

    }

    Value visitUnaryExp(UnaryExpNode* node) {
        if (node->getPrimaryExp() != nullptr) {
            return visitPrimaryExp(node->getPrimaryExp());
        } else {

        }
    }

    Value visitPrimaryExp(PrimaryExpNode* node) {
        if (node->getExp() != nullptr) {
            return visitExp(node->getExp());
        } else if (node->getLVal() != nullptr) {
            return visitLValExp(node->getLVal());
        } else if (node->getNumber() != nullptr) {
            return visitNumber(node->getNumber());
        } else {
            error(); return {};
        }
    }

    Value visitLValExp(LValNode* node) {

    }

    Value visitNumber(NumberNode* node) {
        cout << node->getChild()->getVal() << endl;
        return *(dynamic_cast<Value *>(new ConstantInt(node->getChild()->getVal())));
    }

//    Value trimTo(Value value, FuncType targetType) {
//        return value;
//    }


    void error() {
        cout << "error!" << endl;
    }
};
#endif //TAYILER_VISITOR_H
