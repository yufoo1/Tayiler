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
#include "llvm-ir/Loop.h"
#include "Evaluator.h"
#include "llvm-ir/instr/LoadInstr.h"

class Visitor {

private:
    Manager* manager = nullptr;
    BasicBlock* curBasicBlock = nullptr;
    BasicBlock* globalBasicBlock = nullptr;
    SymbolTable* curSymbolTable = nullptr;
    SymbolTable* globalSymbolTable = nullptr;
    Function* globalFunction = nullptr;
    Function* curFunction = nullptr;
    Loop* curLoop = nullptr;
    Evaluator* evaluator = new Evaluator(curSymbolTable);
    int inLoop = false;
    bool inCond = false;
    int inBranch = false;
    bool inLeft = false; /* judge need Load Instr or not */
    bool hasReturnInstr = false;
    stack<BasicBlock *> loopHeads;
    stack<BasicBlock *> loopFollows;
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
        curLoop = new Loop(nullptr);
        hasReturnInstr = false;
        if(manager->getFunctions().count(node->getIdent()->getVal()) || checkSymbolTable(node->getIdent()->getVal())) {
            errorList.emplace_back(node->getIdent()->getLine(), "b");
        }
        auto* entry = new BasicBlock();
        curLoop->addBasicBlock(entry);
        curBasicBlock = entry;
        curLoop->setHeader(entry);
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
        curLoop->setFunction(function);
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
        if(!hasReturnInstr) {
            new ReturnInstr(curBasicBlock, nullptr, false);
        }
        curSymbolTable = curSymbolTable->getParent();
    }

    void visitMainFuncDef(MainFuncDefNode* node) {
        curLoop = new Loop(nullptr);
        FuncType retType = FuncType::INT32;
        auto* entry = new BasicBlock();
        curLoop->addBasicBlock(entry);
        string ident = ReservedWordMapReversed.at(SyntaxType::MAINTK);
        curBasicBlock = entry;
        curLoop->setHeader(entry);
        curSymbolTable = new SymbolTable(globalSymbolTable);
        auto* function = new Function(curBasicBlock, curSymbolTable, ident, nullptr, nullptr, retType);
        manager->setMainFunction(function);
        curFunction = function;
        curLoop->setFunction(function);
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
        new BrInstr(curBasicBlock, loopFollows.top());
    }

    void visitContinueStmt(StmtNode* node) {
        new BrInstr(curBasicBlock, loopHeads.top());
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
            if(node->getExps().empty()) {
                return getSymbolTermIteratively(node->getIdent()->getVal())->getAllocaInstr();
            } else {
                vector<int> nums = dynamic_cast<AllocaInstr*>(getSymbolTermIteratively(node->getIdent()->getVal())->getAllocaInstr())->getNums();
                Value* ptr = getSymbolTermIteratively(node->getIdent()->getVal())->getAllocaInstr();
                auto* tmp = new vector<int>;
                for(auto i : nums) {
                    tmp->emplace_back(i);
                }
                ptr = new GetElementPtrInstr(curBasicBlock, ptr, nullptr, tmp, curFunction->genInstrIdx());
                Value* offset = CONSTANT_ZERO;
                YASSERT(node->getExps().size() == nums.size())
                for(int i = 0; i < node->getExps().size() - 1; ++i) {
                    tmp = new vector<int>;
                    for(int j = i + 1; j < nums.size(); ++j) {
                        tmp->emplace_back(nums.at(j));
                    }
                    offset = new AluInstr(curBasicBlock,
                                         new AluInstr(curBasicBlock, offset,
                                                      visitExp(dynamic_cast<ExpNode*>(node->getExps().at(i))),
                                                      SyntaxType::PLUS, curFunction->genInstrIdx()),
                                         new ConstantInt(to_string(nums.at(i))),
                                         SyntaxType::MULT, curFunction->genInstrIdx());
                    ptr = new GetElementPtrInstr(curBasicBlock, ptr, nullptr, tmp, curFunction->genInstrIdx());
                }
                offset = new AluInstr(curBasicBlock, offset, visitExp(dynamic_cast<ExpNode *>(node->getExps().back())), SyntaxType::PLUS, curFunction->genInstrIdx());
                if(inLeft) {
                    return new GetElementPtrInstr(curBasicBlock, ptr, offset, nullptr, curFunction->genInstrIdx());
                } else {
                    ptr = new GetElementPtrInstr(curBasicBlock, ptr, offset, nullptr, curFunction->genInstrIdx());
                    return new LoadInstr(curBasicBlock, FuncType::INT32, ptr, curFunction->genInstrIdx());
                }
            }
        }
    }

    void visitIfStmt(StmtNode* node) {
        auto* thenBlock = new BasicBlock();
        curFunction->addBasicBlock(thenBlock);
        curLoop->addBasicBlock(thenBlock);
        auto* followBlock = new BasicBlock();
        curFunction->addBasicBlock(followBlock);
        curLoop->addBasicBlock(followBlock);
        if(node->getStmts().size() != 1) {
            auto* elseBlock = new BasicBlock();
            curFunction->addBasicBlock(elseBlock);
            curLoop->addBasicBlock(elseBlock);
            YASSERT(node->getStmts().size() == 2)
            Value* cond = visitCond(node->getCond(), thenBlock, elseBlock);
            new BrInstr(curBasicBlock, cond, thenBlock, elseBlock);
            curBasicBlock = thenBlock;
            ++inBranch;
            visitStmt(node->getStmts().front());
            --inBranch;
            new BrInstr(curBasicBlock, followBlock);
            curBasicBlock = elseBlock;
            ++inBranch;
            visitStmt(node->getStmts().back());
            --inBranch;
        } else {
            Value* cond = visitCond(node->getCond(), thenBlock, followBlock);
            new BrInstr(curBasicBlock, cond, thenBlock, followBlock);
            curBasicBlock = thenBlock;
            ++inBranch;
            visitStmt(node->getStmts().front());
            --inBranch;
        }
        new BrInstr(curBasicBlock, followBlock);
        curBasicBlock = followBlock;
    }

    Value* visitCond(CondNode* node, BasicBlock* trueBasicBlock, BasicBlock* falseBasicBlock) {
        return visitLOrExp(dynamic_cast<LOrExpNode*>(node->getChild()), trueBasicBlock, falseBasicBlock);
    }

    Value* visitLOrExp(LOrExpNode* node, BasicBlock* trueBasicBlock, BasicBlock* falseBasicBlock) {
        BasicBlock* nextBlock = falseBasicBlock;
        BasicBlock* preFalseBlock = falseBasicBlock;
        bool flag = false;
        if(node->getLAndExps().size() > 1) {
            flag = true;
            nextBlock = new BasicBlock();
            curFunction->addBasicBlock(nextBlock);
            curLoop->addBasicBlock(nextBlock);
        }
        Value* first = visitLAndExp(dynamic_cast<LAndExpNode *>(node->getLAndExps().front()), nextBlock);
        for(int i = 1; i < node->getLAndExps().size(); ++i) {
            if(flag) {
                flag = false;
            } else {
                nextBlock = new BasicBlock();
                curFunction->addBasicBlock(nextBlock);
                curLoop->addBasicBlock(nextBlock);
            }
            new BrInstr(curBasicBlock, first, trueBasicBlock, nextBlock);
            curBasicBlock = nextBlock;
            if(i + 1 < node->getLAndExps().size() - 1) {
                flag = true;
                falseBasicBlock = new BasicBlock();
                curFunction->addBasicBlock(falseBasicBlock);
                curLoop->addBasicBlock(falseBasicBlock);
                nextBlock = falseBasicBlock;
            } else {
                falseBasicBlock = preFalseBlock;
            }
            first = visitLAndExp(dynamic_cast<LAndExpNode *>(node->getLAndExps().at(i)), falseBasicBlock);
        }
        return first;
    }

    Value* visitLAndExp(LAndExpNode* node, BasicBlock* falseBasicBlock) {
        Value* first = visitEqExp(dynamic_cast<EqExpNode *>(node->getEqExps().front()));
        if(node->getEqExps().size() == 1) {
            return first;
        } else {
            for(int i = 1; i < node->getEqExps().size(); ++i) {
                auto* nextBlock = new BasicBlock();
                curFunction->addBasicBlock(nextBlock);
                curLoop->addBasicBlock(nextBlock);
                new BrInstr(curBasicBlock, first, nextBlock, falseBasicBlock);
                curBasicBlock = nextBlock;
                first = visitEqExp(dynamic_cast<EqExpNode *>(node->getEqExps().at(i)));
            }
            return first;
        }
    }

    Value* visitEqExp(EqExpNode* node) {
        Value* first = visitRelExp(dynamic_cast<RelExpNode *>(node->getRelExps().front()));
        if(node->getRelExps().size() == 1) {
            return new IcmpInstr(curBasicBlock, first, CONSTANT_ZERO, SyntaxType::NEQ, curFunction->genInstrIdx());
        } else {
            for(int i = 1; i < node->getRelExps().size(); ++i) {
                first = new IcmpInstr(curBasicBlock, first, visitRelExp(
                        dynamic_cast<RelExpNode *>(node->getRelExps().at(i))), node->getOps().at(i - 1), curFunction->genInstrIdx());
            }
        }
        return first;
    }

    Value* visitRelExp(RelExpNode* node) {
        Value* first = visitAddExp(dynamic_cast<AddExpNode *>(node->getAddExps().front()));
        if(node->getAddExps().size() == 1) {
            return first;
        } else {
            for(int i = 1; i < node->getAddExps().size(); ++i) {
                first = new IcmpInstr(curBasicBlock, first, visitAddExp(
                        dynamic_cast<AddExpNode *>(node->getAddExps().at(i))), node->getOps().at(i - 1), curFunction->genInstrIdx());
            }
            return first;
        }
    }

    void visitLValAssignStmt(StmtNode* node) {
        if(!checkSymbolTable(node->getLVal()->getIdent()->getVal())) {
            errorList.emplace_back(node->getLVal()->getIdent()->getLine(), "c");
        } else if(getSymbolTermIteratively(node->getLVal()->getIdent()->getVal())->getIsConstant()) {
            errorList.emplace_back(node->getLVal()->getIdent()->getLine(), "h");
        } else {
            inLeft = true;
            Value* lVal = visitLVal(node->getLVal());
            inLeft = false;
            new StoreInstr(curBasicBlock, lVal, visitExp(node->getExps().front()));
        }
    }

    void visitPrintfStmt(StmtNode* node) {
        string formatString = node->getFormatString();
        vector<ExpNode*> exps = node->getExps();
        vector<Value*> values;
        for(auto i : exps) {
            values.emplace_back(visitExp(i));
        }
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
                            new PutintInstr(curBasicBlock, values.at(cnt++));
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
        if(inBranch == 0 && inLoop == 0) {
            hasReturnInstr = true;
        }
        new ReturnInstr(curBasicBlock, node->getExps().empty() ? nullptr : visitExp(node->getExps().front()),
                        curFunction->getIdent() == ReservedWordMapReversed.at(SyntaxType::MAINTK));
    }

    void visitWhileStmt(StmtNode* node) {
        curLoop = new Loop(curLoop);
        curLoop->setFunction(curFunction);
        auto* condBlock = new BasicBlock();
        curFunction->addBasicBlock(condBlock);
        curLoop->addBasicBlock(condBlock);
        new BrInstr(curBasicBlock, condBlock);
        auto* whileBasicBlock = new BasicBlock();
        curFunction->addBasicBlock(whileBasicBlock);
        curLoop->addBasicBlock(whileBasicBlock);
        auto* endBasicBlock = new BasicBlock();
        curFunction->addBasicBlock(endBasicBlock);
        curLoop->addBasicBlock(endBasicBlock);
        curBasicBlock = condBlock;
        inCond = true;
        Value* cond = visitCond(node->getCond(), whileBasicBlock, endBasicBlock);
        new BrInstr(curBasicBlock, cond, whileBasicBlock, endBasicBlock);
        curBasicBlock = whileBasicBlock;
        inCond = false;
        loopHeads.push(condBlock);
        loopFollows.push(endBasicBlock);
        ++inLoop;
        visitStmt(node->getStmts().front());
        --inLoop;
        loopHeads.pop();
        loopFollows.pop();
        new BrInstr(curBasicBlock, condBlock);
        curBasicBlock = endBasicBlock;
        curLoop = curLoop->getParent();
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
                if(node->getConstExps().empty()) {
                    auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, node->getIdent()->getVal(), type, isConstant, false, curFunction->genInstrIdx());
                    curSymbolTable->addSymbolTerm(new SymbolTerm(node->getIdent()->getVal(), type, isConstant, node->getConstExps().size(), allocInstr));
                    if (node->getInitVal() != nullptr) {
                        new StoreInstr(curBasicBlock, allocInstr, visitInitVal(node->getInitVal()));
                    }
                } else {
                    vector<int> nums;
                    for(auto i : node->getConstExps()) {
                        nums.emplace_back(evaluator->evalConstExp(dynamic_cast<ConstExpNode*>(i)));
                    }
                    auto* allocInstr = new AllocaInstr(curBasicBlock, curSymbolTable, node->getIdent()->getVal(), type, isConstant, false, curFunction->genInstrIdx(), nums);
                    curSymbolTable->addSymbolTerm(new SymbolTerm(node->getIdent()->getVal(), type, isConstant, node->getConstExps().size(), allocInstr));
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
            YASSERT(mulExps.size() - 1 == ops.size())
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
                    auto* values = new vector<Value*>;
                    if (node->getFuncRParams() != nullptr) {
                        vector<Node*> exps = node->getFuncRParams()->getExps();
                        for(int i = 0; i < exps.size(); ++i) {
                            Value* exp = visitExp(dynamic_cast<ExpNode *>(exps.at(i)));
                            if(exp != nullptr) {
                                if(exp->getFuncType() != manager->getFunction(node->getIdent()->getVal())->getParams()->at(i)->getFuncType() || getDimensionality(dynamic_cast<ExpNode *>(exps.at(i))) != manager->getFunction(node->getIdent()->getVal())->getParams()->at(i)->getDimensionality()) {
                                    errorList.emplace_back(node->getIdent()->getLine(), "e");
                                } else {
                                    values->emplace_back(exp);
                                }
                            }
                        }
                    }
                    auto *allocaInstrs = new vector<AllocaInstr*>;
                    for (auto i: *manager->getFunction(node->getIdent()->getVal())->getParams()) {
                        allocaInstrs->emplace_back(dynamic_cast<AllocaInstr *>
                                                   (manager->getFunction(node->getIdent()->getVal())->getSymbolTable()->getSymbolTerm(i->getIdent())->getAllocaInstr()));
                    }
                    return new CallInstr(curBasicBlock, manager->getFunction(node->getIdent()->getVal()), values, allocaInstrs, curFunction->genInstrIdx());
                }
            }
        } else if (node->getUnaryOp() != SyntaxType::NONE) {
            Value* unaryExp = visitUnaryExp(node->getUnaryExp());
            unaryExp->setFuncType(FuncType::INT32);
            switch (node->getUnaryOp()) {
                case SyntaxType::MINU: {
                    unaryExp = new AluInstr(curBasicBlock == nullptr ? globalBasicBlock : curBasicBlock, CONSTANT_ZERO, unaryExp, node->getUnaryOp(), curFunction->genInstrIdx());
                    break;
                }
                case SyntaxType::NOT: {
                    unaryExp = new IcmpInstr(curBasicBlock == nullptr ? globalBasicBlock : curBasicBlock, CONSTANT_ZERO, unaryExp, SyntaxType::EQL, curFunction->genInstrIdx());
                    break;
                }
                default: break;
            }
            return unaryExp;
        } else {
            error(); return nullptr;
        }
        error(); return nullptr;
    }

    int getDimensionality(ExpNode* node) {
        auto* addExp = dynamic_cast<AddExpNode *>(node->getChild());
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
        auto* constantInt = new ConstantInt(node->getChild()->getVal());
        auto* aluInstr = new AluInstr(curBasicBlock == nullptr ? globalBasicBlock : curBasicBlock, CONSTANT_ZERO, constantInt, SyntaxType::PLUS, curFunction == nullptr ? 0 : curFunction->genInstrIdx());
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
