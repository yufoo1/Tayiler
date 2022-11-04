//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_NODE_H
#define TAYILER_NODE_H
#include "tuple"
#include <fstream>
#include <utility>
#include "../parser/ParseCursor.h"
#include "iostream"
#include "../lexer/SyntaxType.h"
#include "../parser/SyntaxTree.h"
#include "../utils/handler.h"

using namespace std;
class Node {
protected:
    Node* child = nullptr;
private:
    string val; /* if instr, val is the virtual register allocated, else if constantInt, val is the value of the constantInt. */
public:
    explicit Node() = default;

    explicit Node(string val) {
        this->val = move(val);
    }

    string getVal() {
        return val;
    }

    virtual void insertList(vector<tuple<SyntaxType, string>>* parserList, string val) {
        cout << "This method should be override!" << "\n";
    }

    virtual void insertList(vector<tuple<SyntaxType, string>>* parserList) {
        cout << "This method should be override!" << "\n";
    }

    virtual SyntaxType getType() {
        cout << "This method should be override!" << "\n";
        return SyntaxType::NONE;
    }

    virtual void insertNode(Node* node) {
        child = node;
    }

    Node* getChild() {
        return child;
    }

};


#endif //TAYILER_NODE_H
