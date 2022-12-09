//
// Created by yufoo1 on 2022/12/9.
//

#ifndef TAYILER_LOOP_H
#define TAYILER_LOOP_H

#include <vector>
#include <string>
class BasicBlock;
class Function;
using namespace std;
class Loop {
private:
    string label;
    Loop* parent = nullptr;
    vector<Loop*> childs;
    BasicBlock* header = nullptr;
    Function* function = nullptr;
    set<BasicBlock *> nowLevelBasicBlocks;

public:
    explicit Loop(Loop* parent) {
        this->parent = parent;
        if(parent != nullptr) {
            parent->addChildLoop(this);
            label = parent->getLabel() + "-" + to_string(getDepth());
        } else {
            label = "nullptr-" + to_string(getDepth());
        }
    }

    string getLabel() {
        return label;
    }

    int getDepth() {
        if(parent == nullptr) {
            return 0;
        } else {
            return parent->getDepth() + 1;
        }
    }

    void addChildLoop(Loop* child) {
        childs.emplace_back(child);
    }

    void setHeader(BasicBlock* header) {
        this->header = header;
    }

    void setFunction(Function* function) {
        this->function = function;
    }

    BasicBlock* getHeader() {
        return header;
    }

    Function* getFunction() {
        return function;
    }

    bool addBasicBlock(BasicBlock* basicBlock) {
        if(nowLevelBasicBlocks.count(basicBlock)) {
            return false;
        } else {
            nowLevelBasicBlocks.insert(basicBlock);
            return true;
        }
    }

    Loop* getParent() {
        return parent;
    }

};
#endif //TAYILER_LOOP_H
