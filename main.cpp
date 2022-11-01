#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "llvm-ir-gen/Visitor.h"

int main() {
    const char* inputFile = "../testfile.txt", * outputFile = "../output.txt", * llvmFile = "../llvm.ll";
    Lexer lexer(inputFile, outputFile);
    Parser parser(lexer.getLexerList(), outputFile);
    Visitor visitor(parser.getSyntaxTreeRoot(), llvmFile);
    return 0;
}
