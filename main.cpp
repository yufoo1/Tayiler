#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "llvm-ir-gen/Visitor.h"

int main() {
    const char* inputFile = "../testfile.txt", * outputFile = "../output.txt";
    Lexer lexer(inputFile, outputFile);
    Parser parser(lexer.getLexerList(), outputFile);
    return 0;
}
