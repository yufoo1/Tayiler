//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LEXCURSOR_H
#define TAYILER_LEXCURSOR_H
#include <utility>
#include "iostream"
#include "set"

using namespace std;

class LexCursor {
private:
    string fileString;
    int curIndex;
    set<char> BlankSet = {
            ' ', '\n', '\r', '\t'
    };

public:
    explicit LexCursor(string fileString) {
        this->fileString = move(fileString);
        skipBlank();
        curIndex = 0;
    }

    char getNthToken(int n) {
        return (curIndex + n >= fileString.length()) ? EOF : fileString.at(curIndex + n);
    }

    void next(int n) {
        curIndex += n;
    }

    string scanWord() {
        string w;
        char c;
        c = scanToken();
        w += c;
        if (c == '"') {
            while ((c = scanToken()) != '"') {
                w += c;
            }
            w += c;
            return w;
        } else {
            while (true) {
                c = scanToken();
                if (isdigit(c) || isalpha(c) || c == '_') {
                    w += c;
                } else {
                    break;
                }
            }
        }
        next(-1);
        return w;
    }

    char scanToken() {
        curIndex++;
        return curIndex > fileString.length() ? EOF : fileString.at(curIndex - 1);
    }

    void skipLineComment() {
        while (scanToken() != '\n');
    }

    void skipMultilineComment() {
        while (!(getNthToken(0) == '*' && getNthToken(1) == '/')) {
            next(1);
        }
        next(2);
    }

    void skipBlank() {
        while (BlankSet.count(scanToken()));
        next(-1);
    }

    bool judgeEnd() {
        return curIndex >= fileString.length();
    }
};
#endif //TAYILER_LEXCURSOR_H
