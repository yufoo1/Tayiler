//
// Created by yufoo1 on 2022/10/27.
//

#ifndef TAYILER_FILEHELPER_H
#define TAYILER_FILEHELPER_H

#include <vector>
#include "iostream"
#include "../lexer/SyntaxType.h"

using namespace std;
class FileHelper {
private:
    vector<tuple<SyntaxType, string>>* lexerList = nullptr;
    vector<tuple<SyntaxType, string>>* parseList = nullptr;
    ifstream* input = nullptr;
    ofstream* output = nullptr;
public:
    static FileHelper fileHelper;

    FileHelper(string inputFile, string outputFile) {

    }

    void setLexerList(vector<tuple<SyntaxType, string>>* lexerList) {
        this->lexerList = lexerList;
    }

    void outputLexerList(vector<tuple<SyntaxType, string>>* parseList) {
        this->parseList = parseList;
    }
};
#endif //TAYILER(_FILEHELPER_H
