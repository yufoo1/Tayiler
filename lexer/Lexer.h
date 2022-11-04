//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_LEXER_H
#define TAYILER_LEXER_H

#include <fstream>
#include "SyntaxType.h"
#include "LexCursor.h"
#include "regex"
#include "iostream"

using namespace std;

class Lexer {
private:
    vector<tuple<SyntaxType, string>> lexerList;
    LexCursor* cursor = nullptr;
    tuple<bool, SyntaxType, string> lex() {
        char first = cursor->scanToken();
        switch (first) {
            case '!':
                if (cursor->getNthToken(0) == '=') {
                    cursor->next(1);
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::NEQ, TokenMap.at(SyntaxType::NEQ)};
                } else {
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::NOT, TokenMap.at(SyntaxType::NOT)};
                }
            case '&':
                cursor->next(1);
                return tuple<bool, SyntaxType, string> {true, SyntaxType::AND, TokenMap.at(SyntaxType::AND)};
            case '-':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::MINU, TokenMap.at(SyntaxType::MINU)};
            case '/':
                switch (cursor->getNthToken(0)) {
                    case '/':
                        cursor->next(1);
                        cursor->skipLineComment();
                        cursor->skipBlank();
                        if (!cursor->judgeEnd()) {
                            return lex();
                        } else {
                            return tuple<bool, SyntaxType, string> {false, SyntaxType::NONE, ""};
                        }
                    case '*':
                        cursor->next(1);
                        cursor->skipMultilineComment();
                        cursor->skipBlank();
                        if (!cursor->judgeEnd()) {
                            return lex();
                        } else {
                            return tuple<bool, SyntaxType, string> {false, SyntaxType::NONE, ""};
                        }
                    default:
                        return tuple<bool, SyntaxType, string> {true, SyntaxType::DIV, TokenMap.at(SyntaxType::DIV)};
                }
            case '%':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::MOD, TokenMap.at(SyntaxType::MOD)};
            case '<':
                if (cursor->getNthToken(0) == '=') {
                    cursor->next(1);
                    return tuple<bool, SyntaxType , string> {true, SyntaxType::LEQ, TokenMap.at(SyntaxType::LEQ)};
                } else {
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::LSS, TokenMap.at(SyntaxType::LSS)};
                }
            case '>':
                if (cursor->getNthToken(0) == '=') {
                    cursor->next(1);
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::GEQ, TokenMap.at(SyntaxType::GEQ)};
                } else {
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::GRE, TokenMap.at(SyntaxType::GRE)};
                }
            case '=':
                if (cursor->getNthToken(0) == '=') {
                    cursor->next(1);
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::EQL, TokenMap.at(SyntaxType::EQL)};
                } else {
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::ASSIGN, TokenMap.at(SyntaxType::ASSIGN)};
                }
            case ';':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::SEMICN, TokenMap.at(SyntaxType::SEMICN)};
            case ',':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::COMMA, TokenMap.at(SyntaxType::COMMA)};
            case '|':
                cursor->next(1);
                return tuple<bool, SyntaxType, string> {true, SyntaxType::OR, TokenMap.at(SyntaxType::OR)};
            case '+':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::PLUS, TokenMap.at(SyntaxType::PLUS)};
            case '*':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::MULT, TokenMap.at(SyntaxType::MULT)};
            case '(':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::LPARENT, TokenMap.at(SyntaxType::LPARENT)};
            case ')':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::RPARENT, TokenMap.at(SyntaxType::RPARENT)};
            case '[':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::LBRACK, TokenMap.at(SyntaxType::LBRACK)};
            case ']':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::RBRACK, TokenMap.at(SyntaxType::RBRACK)};
            case '{':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::LBRACE, TokenMap.at(SyntaxType::LBRACE)};
            case '}':
                return tuple<bool, SyntaxType, string> {true, SyntaxType::RBRACE, TokenMap.at(SyntaxType::RBRACE)};
            default:
                cursor->next(-1);
                string w = cursor->scanWord();
                if (ReservedWordMap.count(w)) {
                    return tuple<bool, SyntaxType, string> {true, ReservedWordMap.at(w), w};
                } else if (regex_match(w, regex("^\\d+$"))) {
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::INTCON, w};
                } else if (regex_match(w, regex("^\".*?\"$"))) {
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::STRCON, w};
                } else {
                    return tuple<bool, SyntaxType, string> {true, SyntaxType::IDENFR, w};
                }

        }
    }

public:
    explicit Lexer(ifstream* f) {
        cursor = new LexCursor(fileRead(f));
        while (!cursor->judgeEnd()) {
            cursor->skipBlank();
            auto t = lex();
            if (get<0>(t)) {
                lexerList.emplace_back(get<1>(t), get<2>(t));
                cursor->skipBlank();
            }
        }
    }

    static string fileRead(ifstream* f) {
        if (!f->is_open()) {
            cout << "error happened when open!" << endl;
        }
        string line, fileString;
        while (getline(*f, line)) {
            fileString += line + "\n";
            line.clear();
        }
        f->close();
        return fileString;
    }

    void fileWrite(ofstream* f) {
        for (auto i : lexerList) {
            *f << SyntaxType2String.at(std::get<0>(i)) << " " << std::get<1>(i) << "\n";
        }
    }

    vector<tuple<SyntaxType, string>> getLexerList() {
        return lexerList;
    }
};


#endif //TAYILER_LEXER_H
