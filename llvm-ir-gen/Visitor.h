//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_VISITOR_H
#define TAYILER_VISITOR_H

#include "../node/Node.h"
#include "Manager.h"
#include "llvm-ir/instr/StoreInstr.h"
#include "llvm-ir/constant/ConstantInt.h"
#include "llvm-ir/instr/AllocaInstr.h"
#include "llvm-ir/instr/GetintInstr.h"
#include "llvm-ir/instr/GetElementPtrInstr.h"
#include "llvm-ir/instr/PutstrInstr.h"
#include "llvm-ir/instr/PutintInstr.h"
#include "llvm-ir/instr/CallInstr.h"

class Visitor {
public:
    Visitor(Node* root) {
        manager = new Manager;
        visitAst(root);
        manager->dumpLLVM("llvm.ll");
    }

private:
    Manager* manager;
    BasicBlock* curBasicBlock;
    SymbolTable* curSymbolTable;
    map<string, AllocaInstr*> ident2AllocaInstr; /* TODO  need merge into SymbolTable */
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
        auto *params = new vector<Param*>;
        auto* entry = new BasicBlock();
        curBasicBlock = entry;
        curSymbolTable = new SymbolTable(curSymbolTable);
        if (node->getFunFParams() != nullptr) {
            for (auto i : node->getFunFParams()->getFuncFParams()) {
                auto* param = new Param(dynamic_cast<FuncFParamNode*>(i)->getIdent(), SyntaxType2FuncType.at(dynamic_cast<FuncFParamNode*>(i)->getBType()->getChild()->getType()));
                params->emplace_back(param);
            }
        }
        auto* function = new Function(node->getIdent(), params, SyntaxType2FuncType.at(node->getFuncType()->getTokenType()));
        manager->addFunction(function);
        function->setBody(entry);
        function->addBasicBlock(entry);
        curFunction = function;
        entry->setFunction(curFunction);
        for (auto i : *params) {
            auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, i->getIdent(), i->getType(), false, true, curFunction->genInstrIdx());
            ident2AllocaInstr.insert({allocInstr->getIdent(), allocInstr});
            i->setVal(allocInstr->getVal());
        }
        visitBlock(node->getBlock());
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
        function->addBasicBlock(entry);
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

    Value* visitExpStmt(StmtNode* node) {
        visitExp(node->getExps().front());
    }

    void visitGetintStmt(StmtNode* node) {
        new GetintInstr(curBasicBlock, visitLVal(node->getLVal()));
    }

    Value* visitLVal(LValNode* node) {
        return ident2AllocaInstr.at(node->getIdent());
    }

    void visitIfStmt(StmtNode* node) {

    }

    void visitLValAssignStmt(StmtNode* node) {
        Value* lVal = visitLVal(node->getLVal());
        /* TODO array */
        Value* exp = visitExp(node->getExps().front());
        new StoreInstr(curBasicBlock, lVal, exp);
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
                    auto* globalString = new GlobalString(str, FuncType::INT8);
                    GLOBALSTRINGS.insert(globalString);
                    auto* instr = new GetElementPtrInstr(curBasicBlock, globalString, curFunction->genInstrIdx());
                    new PutstrInstr(curBasicBlock, instr);
                }
                if (formatString.at(i) == '%') {
                    if (formatString.at(++i) == 'd') {
                        new PutintInstr(curBasicBlock, visitExp(exps.at(cnt++)));
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
        if (node->getExps().empty()) {
            new ReturnInstr(curBasicBlock);
        } else {
            Value* value = visitExp(node->getExps().front());
            new ReturnInstr(curBasicBlock, value);
        }
    }

    void visitWhileStmt(StmtNode* node) {

    }

    void visitSemicnStmt(StmtNode* node) {

    }

    void visitDecl(DeclNode* node) {
        switch (node->getChild()->getType()) {
            case SyntaxType::CONSTDECL: visitConstDecl(dynamic_cast<ConstDeclNode *>(node->getChild())); break;
            case SyntaxType::VARDECL: visitVarDecl(dynamic_cast<VarDeclNode *>(node->getChild())); break;
            default: error(); break;
        }
    }

    void visitConstDecl(ConstDeclNode* node) {

    }

    void visitVarDecl(VarDeclNode* node) {
        FuncType type = visitBType(node->getBType());
        vector<Node*> varDefs = node->getVarDefs();
        for (auto i : varDefs) visitVarDef(dynamic_cast<VarDefNode *>(i), type);
    }

    void visitVarDef(VarDefNode* node, FuncType type) {
        /* TODO: without array */
        AllocaInstr* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, node->getIdent(), type, false, false, curFunction->genInstrIdx());
        ident2AllocaInstr.insert({allocInstr->getIdent(), allocInstr});
        if (node->getInitVal() != nullptr) {
            new StoreInstr(curBasicBlock, allocInstr, visitInitVal(node->getInitVal()));
        }
    }

    Value* visitInitVal(InitValNode* node) {
        if (node->getExp() != nullptr) {
            return visitExp(node->getExp());
        } else {
            /* TODO {InitVal{...}}*/
            error();
        }
    }

    FuncType visitBType(BTypeNode* node) {
        switch (node->getChild()->getType()) {
            case SyntaxType::INTTK: return FuncType::INT32;
            default: break;
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
            Value* mulExp = visitMulExp(dynamic_cast<MulExpNode *>(mulExps.back()));
            assert(mulExps.size() - 1 == ops.size());
            for (int i = ops.size() - 1; i >= 0; i--) {
                mulExp = new AluInstr(curBasicBlock, visitMulExp(dynamic_cast<MulExpNode *>(mulExps.at(i))), mulExp, ops.at(i), curFunction->genInstrIdx());
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
            Value* unaryExp = visitUnaryExp(dynamic_cast<UnaryExpNode *>(unaryExps.back()));
            assert(unaryExps.size() - 1 == ops.size());
            for (int i = ops.size() - 1; i >= 0; i--) {
                unaryExp = new AluInstr(curBasicBlock, visitUnaryExp(dynamic_cast<UnaryExpNode *>(unaryExps.at(i))), unaryExp, ops.at(i), curFunction->genInstrIdx());
            }
            return unaryExp;
        }

    }

    Value* visitUnaryExp(UnaryExpNode* node) {
        if (node->getPrimaryExp() != nullptr) {
            return visitPrimaryExp(node->getPrimaryExp());
        } else if (!node->getIdent().empty()) {
            vector<Value*> values;
            if (node->getFuncRParams() != nullptr) {
                for (auto i : node->getFuncRParams()->getExps()) {
                    values.emplace_back(visitExp(dynamic_cast<ExpNode *>(i)));
                }
            }
            new CallInstr(curBasicBlock, manager->getFunction(node->getIdent())->getIdent(), manager->getFunction(node->getIdent())->getRetType(), values);
        } else if (node->getUnaryOp() != SyntaxType::NONE) {
            Value* unaryExp = visitUnaryExp(node->getUnaryExp());
            unaryExp->setFuncType(FuncType::INT32);
            switch (node->getUnaryOp()) {
                case SyntaxType::MINU:
                    unaryExp = new AluInstr(curBasicBlock, CONSTANT_ZERO, unaryExp, node->getUnaryOp(), curFunction->genInstrIdx());
                    break;
                default: break;
            }
            return unaryExp;
        } else {
            error(); return {};
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
            error(); return {};
        }
    }

    Value* visitNumber(NumberNode* node) {
        auto constInt = new ConstantInt(node->getChild()->getVal());
        return constInt;
    }

//    Value trimTo(Value value, FuncType targetType) {
//        return value;
//    }


    void error() {
        cout << "error!" << endl;
    }
};
#endif //TAYILER_VISITOR_H
