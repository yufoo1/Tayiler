//
// Created by yufoo1 on 2022/10/24.
//

#ifndef TAYILER_SYNTAXTYPE_H
#define TAYILER_SYNTAXTYPE_H

#include "iostream"
#include "map"

enum class SyntaxType {
    NONE,
    IDENFR, INTCON, STRCON,
    MAINTK, INTTK, VOIDTK, CONSTTK, BREAKTK, CONTINUETK, IFTK, ELSETK, WHILETK, RETURNTK,  GETINTTK, PRINTFTK,
    NOT, AND, OR, PLUS, MINU, MULT, DIV, MOD, LSS, LEQ, GRE, GEQ, EQL, NEQ, ASSIGN,
    SEMICN, COMMA, LPARENT, RPARENT, LBRACK, RBRACK, LBRACE, RBRACE,

    ADDCONSTEXP, ADDEXP, BLOCKITEM, BLOCK, BTYPE, COMPUNIT, COND, CONSTDECL, CONSTDEF, CONSTEXP, CONSTINITVAL, DECL,
    EQEXP, EXP, FUNCDEF, FUNCFPARAM, FUNCFPARAMS, FUNCRPARAMS, FUNCTYPE, INITVAL, INTCONST,
    LANDEXP, LOREXP, LVAL, MAINFUNCDEF, MULEXP, NUMBER, PRIMARYEXP, RELEXP, STMT, UNARYEXP, UNARYOP, VARDECL, VARDEF,
};

enum class StmtType {
    NONE, BLOCK, BREAK, CONTINUE, EXP, GETINT, IF, LVALASSIGN, PRINTF, RETURN, WHILE, SEMICN
};

enum class CallInstrType {
    NONE, GETINT, PUTINT, PUTCH, PUTSTR
};

std::map<CallInstrType, std::string> CallInstrType2String = {
        {CallInstrType::GETINT, "getint"},
        {CallInstrType::PUTINT, "putint"},
        {CallInstrType::PUTCH,  "putch"},
        {CallInstrType::PUTSTR, "putstr"},
};

enum class FuncType {
    INT1, INT8, INT32, VOID, INT8PTR
};

std::map<FuncType, std::string> FuncType2String = {
        {FuncType::INT1, "i1"},
        {FuncType::INT8, "i8"},
        {FuncType::INT32, "i32"},
        {FuncType::VOID, "void"},
        {FuncType::INT8PTR, "i8*"},
};

std::map<std::string, SyntaxType> ReservedWordMap = {
        {"main", SyntaxType::MAINTK},
        {"const", SyntaxType::CONSTTK},
        {"int", SyntaxType::INTTK},
        {"break", SyntaxType::BREAKTK},
        {"continue", SyntaxType::CONTINUETK},
        {"if", SyntaxType::IFTK},
        {"else", SyntaxType::ELSETK},
        {"while", SyntaxType::WHILETK},
        {"getint", SyntaxType::GETINTTK},
        {"printf", SyntaxType::PRINTFTK},
        {"return", SyntaxType::RETURNTK},
        {"void", SyntaxType::VOIDTK},
};

std::map<SyntaxType, std::string> ReservedWordMapReversed = {
        {SyntaxType::MAINTK, "main"},
        {SyntaxType::CONSTTK, "const"},
        {SyntaxType::INTTK, "int"},
        {SyntaxType::BREAKTK, "break"},
        {SyntaxType::CONTINUETK, "continue"},
        {SyntaxType::IFTK, "if"},
        {SyntaxType::ELSETK, "else"},
        {SyntaxType::WHILETK, "while"},
        {SyntaxType::GETINTTK, "getint"},
        {SyntaxType::PRINTFTK, "printf"},
        {SyntaxType::RETURNTK, "return"},
        {SyntaxType::VOIDTK, "void"},
};

std::map<SyntaxType, std::string> TokenMap = {
        {SyntaxType::NOT, "!"},
        {SyntaxType::AND, "&&"},
        {SyntaxType::MINU, "-"},
        {SyntaxType::DIV, "/"},
        {SyntaxType::MOD, "%"},
        {SyntaxType::LSS, "<"},
        {SyntaxType::LEQ, "<="},
        {SyntaxType::GRE, ">"},
        {SyntaxType::GEQ, ">="},
        {SyntaxType::EQL, "=="},
        {SyntaxType::NEQ, "!="},
        {SyntaxType::ASSIGN, "="},
        {SyntaxType::SEMICN, ";"},
        {SyntaxType::COMMA, ","},
        {SyntaxType::OR, "||"},
        {SyntaxType::PLUS, "+"},
        {SyntaxType::MULT, "*"},
        {SyntaxType::LPARENT, "("},
        {SyntaxType::RPARENT, ")"},
        {SyntaxType::LBRACK, "["},
        {SyntaxType::RBRACK, "]"},
        {SyntaxType::LBRACE, "{"},
        {SyntaxType::RBRACE, "}"}
};

std::map<SyntaxType, std::string> SyntaxType2String = {
        {SyntaxType::NONE, "NONE"},
        {SyntaxType::IDENFR, "IDENFR"},
        {SyntaxType::INTCON, "INTCON"},
        {SyntaxType::STRCON, "STRCON"},
        {SyntaxType::MAINTK, "MAINTK"},
        {SyntaxType::INTTK, "INTTK"},
        {SyntaxType::VOIDTK, "VOIDTK"},
        {SyntaxType::CONSTTK, "CONSTTK"},
        {SyntaxType::BREAKTK, "BREAKTK"},
        {SyntaxType::CONTINUETK, "CONTINUETK"},
        {SyntaxType::IFTK, "IFTK"},
        {SyntaxType::ELSETK, "ELSETK"},
        {SyntaxType::WHILETK, "WHILETK"},
        {SyntaxType::RETURNTK, "RETURNTK"},
        {SyntaxType::GETINTTK, "GETINTTK"},
        {SyntaxType::PRINTFTK, "PRINTFTK"},
        {SyntaxType::NOT, "NOT"},
        {SyntaxType::AND, "AND"},
        {SyntaxType::OR, "OR"},
        {SyntaxType::PLUS, "PLUS"},
        {SyntaxType::MINU, "MINU"},
        {SyntaxType::MULT, "MULT"},
        {SyntaxType::DIV, "DIV"},
        {SyntaxType::MOD, "MOD"},
        {SyntaxType::LSS, "LSS"},
        {SyntaxType::LEQ, "LEQ"},
        {SyntaxType::GRE, "GRE"},
        {SyntaxType::GEQ, "GEQ"},
        {SyntaxType::EQL, "EQL"},
        {SyntaxType::NEQ, "NEQ"},
        {SyntaxType::ASSIGN, "ASSIGN"},
        {SyntaxType::SEMICN, "SEMICN"},
        {SyntaxType::COMMA, "COMMA"},
        {SyntaxType::LPARENT, "LPARENT"},
        {SyntaxType::RPARENT, "RPARENT"},
        {SyntaxType::LBRACK, "LBRACK"},
        {SyntaxType::RBRACK, "RBRACK"},
        {SyntaxType::LBRACE, "LBRACE"},
        {SyntaxType::RBRACE, "RBRACE"},
        {SyntaxType::ADDCONSTEXP, "AddConstExp"},
        {SyntaxType::ADDEXP, "AddExp"},
        {SyntaxType::BLOCKITEM, "BlockItem"},
        {SyntaxType::BLOCK, "Block"},
        {SyntaxType::BTYPE, "BType"},
        {SyntaxType::COMPUNIT, "CompUnit"},
        {SyntaxType::COND, "Cond"},
        {SyntaxType::CONSTDECL, "ConstDecl"},
        {SyntaxType::CONSTDEF, "ConstDef"},
        {SyntaxType::CONSTEXP, "ConstExp"},
        {SyntaxType::CONSTINITVAL, "ConstInitVal"},
        {SyntaxType::DECL, "Decl"},
        {SyntaxType::EQEXP, "EqExp"},
        {SyntaxType::EXP, "Exp"},
        {SyntaxType::FUNCDEF, "FuncDef"},
        {SyntaxType::FUNCFPARAM, "FuncFParam"},
        {SyntaxType::FUNCFPARAMS, "FuncFParams"},
        {SyntaxType::FUNCRPARAMS, "FuncRParams"},
        {SyntaxType::FUNCTYPE, "FuncType"},
        {SyntaxType::INITVAL, "InitVal"},
        {SyntaxType::INTCONST, "IntConst"},
        {SyntaxType::LANDEXP, "LAndExp"},
        {SyntaxType::LOREXP, "LOrExp"},
        {SyntaxType::LVAL, "LVal"},
        {SyntaxType::MAINFUNCDEF, "MainFuncDef"},
        {SyntaxType::MULEXP, "MulExp"},
        {SyntaxType::NUMBER, "Number"},
        {SyntaxType::PRIMARYEXP, "PrimaryExp"},
        {SyntaxType::RELEXP, "RelExp"},
        {SyntaxType::STMT, "Stmt"},
        {SyntaxType::UNARYEXP, "UnaryExp"},
        {SyntaxType::UNARYOP, "UnaryOp"},
        {SyntaxType::VARDECL, "VarDecl"},
        {SyntaxType::VARDEF, "VarDef"},
};


#endif //TAYILER_SYNTAXTYPE_H
