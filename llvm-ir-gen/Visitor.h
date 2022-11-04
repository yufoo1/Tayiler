//
// Created by yufoo1 on 2022/10/26.
//

#ifndef TAYILER_VISITOR_H
#define TAYILER_VISITOR_H

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
static map<SymbolTable*, map<string, AllocaInstr*>*> SYMBOLTABLE2IDENT2ALLOCAINSTR; /* TODO need merge into SymbolTable */
class Visitor {
public:
    explicit Visitor(Node* root, const char *outputFile) {
        manager = new Manager;
        visitAst(root);
    }

private:
    Manager* manager;
    BasicBlock* curBasicBlock{};
    SymbolTable* curSymbolTable{};
    Function* curFunction{};

    void visitAst(Node* root) {
        visitCompUnit(dynamic_cast<CompUnitNode *>(root));
    }

    void visitCompUnit(CompUnitNode* node) {
        for (auto i : (node->getDeclVec())) visitDecl(dynamic_cast<DeclNode *>(i), true);
        for (auto i : (node->getFuncDefVec())) visitFuncDef(dynamic_cast<FuncDefNode *>(i));
        visitMainFuncDef(node->getMainFuncDef());
    }

    void visitFuncDef(FuncDefNode* node) {
        auto* entry = new BasicBlock();
        curBasicBlock = entry;
        curSymbolTable = new SymbolTable(curSymbolTable);
        SYMBOLTABLE2IDENT2ALLOCAINSTR.insert({curSymbolTable, new map<string, AllocaInstr *>});
        auto *params = new vector<Param*>;
        if (node->getFunFParams() != nullptr) {
            for (auto i : node->getFunFParams()->getFuncFParams()) {
                auto* param = new Param(dynamic_cast<FuncFParamNode*>(i)->getIdent(), SyntaxType2FuncType.at(dynamic_cast<FuncFParamNode*>(i)->getBType()->getChild()->getType()));
                params->emplace_back(param);
            }
        }
        auto* function = new Function(entry, curSymbolTable, node->getIdent(), params, SyntaxType2FuncType.at(node->getFuncType()->getTokenType()));
        curFunction = function;
        manager->addFunction(function);
        for (auto i : *params) {
            auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, i->getIdent(), i->getFuncType(), false, true, curFunction->genInstrIdx());
            SYMBOLTABLE2IDENT2ALLOCAINSTR.at(curSymbolTable)->insert({allocInstr->getIdent(), allocInstr});
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
        SYMBOLTABLE2IDENT2ALLOCAINSTR.insert({curSymbolTable, new map<string, AllocaInstr *>});
        auto* function = new Function(curBasicBlock, curSymbolTable, ident, nullptr, retType);
        manager->setMainFunction(function);
        curFunction = function;
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
            case SyntaxType::DECL: visitDecl(dynamic_cast<DeclNode *>(node->getChild()), false); break;
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
        new GetintInstr(curBasicBlock, visitLVal(node->getLVal()));
    }

    Value* visitLVal(LValNode* node) {
        return SYMBOLTABLE2IDENT2ALLOCAINSTR.at(curSymbolTable)->at(node->getIdent());
    }

    void visitIfStmt(StmtNode* node) {

    }

    void visitLValAssignStmt(StmtNode* node) {
        /* TODO array */
        new StoreInstr(curBasicBlock, visitLVal(node->getLVal()), visitExp(node->getExps().front()));
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
        new ReturnInstr(curBasicBlock, node->getExps().empty() ? nullptr : visitExp(node->getExps().front()),
                        curFunction->getIdent() == ReservedWordMapReversed.at(SyntaxType::MAINTK));
    }

    void visitWhileStmt(StmtNode* node) {

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
        auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, node->getIdent(), type, isConstant, false, curFunction->genInstrIdx());
        SYMBOLTABLE2IDENT2ALLOCAINSTR.at(curSymbolTable)->insert({allocInstr->getIdent(), allocInstr});
        new StoreInstr(curBasicBlock, allocInstr, visitConstInitVal(node->getConstInitVal()));
        if (isGlobal) {
            GLOBALINTS.insert(new GlobalInt(allocInstr));
        }
    }

    Value* visitConstInitVal(ConstInitValNode* node) {
        if (node->getConstExp() != nullptr) {
            return visitConstExp(node->getConstExp());
        } else {
            /* TODO {InitVal{...}}*/
            error();
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
        auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, node->getIdent(), type, isConstant, false, curFunction->genInstrIdx());
        SYMBOLTABLE2IDENT2ALLOCAINSTR.at(curSymbolTable)->insert({allocInstr->getIdent(), allocInstr});
        if (node->getInitVal() != nullptr) {
            new StoreInstr(curBasicBlock, allocInstr, visitInitVal(node->getInitVal()));
        }
        if (isGlobal) {
            GLOBALINTS.insert(new GlobalInt(allocInstr));
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
            vector<Value *>* values = new vector<Value*>;
            if (node->getFuncRParams() != nullptr) {
                for (auto i: node->getFuncRParams()->getExps()) {
                    values->emplace_back(visitExp(dynamic_cast<ExpNode *>(i)));
                }
            }
            vector<AllocaInstr *> *allocaInstrs = new vector<AllocaInstr*>;
            for (auto i: *manager->getFunction(node->getIdent())->getParams()) {
                allocaInstrs->emplace_back(
                        SYMBOLTABLE2IDENT2ALLOCAINSTR.at(manager->getFunction(node->getIdent())->getSymbolTable())->at(
                                i->getIdent()));
            }
            return new CallInstr(curBasicBlock, manager->getFunction(node->getIdent()), values, allocaInstrs);
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
            error(); return { };
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
            error(); return { };
        }
    }

    Value* visitNumber(NumberNode* node) {
        Value* value = new ConstantInt(node->getChild()->getVal());
        new AluInstr(curBasicBlock, CONSTANT_ZERO, value, SyntaxType::PLUS, curFunction->genInstrIdx());
        return value;
    }

//    Value trimTo(Value value, FuncType targetType) {
//        return value;
//    }

    void error() {
        cout << "error!" << endl;
    }

public:
    Manager* getManager() {
        return manager;
    }
};
#endif //TAYILER_VISITOR_H
