#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "llvm-ir-gen/Visitor.h"

int main() {
    const char* inputFile = "testfile.txt",
                * outputFile = "output.txt",
                * llvmFile = "llvm.ll",
                * mipsFile = "mips.txt";
    Lexer lexer(inputFile, outputFile);
    Parser parser(lexer.getLexerList(), outputFile);
    Visitor visitor(parser.getSyntaxTreeRoot(), llvmFile);
//    visitor.getManager()->dumpLlvm(llvmFile);
    visitor.getManager()->dumpMips(mipsFile);
    return 0;
}
