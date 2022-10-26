//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_NODE_H
#define TAYILER_NODE_H
#include "vector"
#include "tuple"
#include <fstream>
#include "../parser/ParseCursor.h"
#include "iostream"
#include "../lexer/SyntaxType.h"

using namespace std;
class Node {
protected:
    vector<Node*> nodes;
public:

    void insertNodes(Node* node) {
        nodes.insert(nodes.begin(), node);
    }

    virtual void insertList(vector<tuple<SyntaxType, string>>* parserList, string val) {
        cout << "This method should be override!" << "\n";
    }

    virtual void insertList(vector<tuple<SyntaxType, string>>* parserList) {
        cout << "This method should be override!" << "\n";
    }

};


#endif //TAYILER_NODE_H
