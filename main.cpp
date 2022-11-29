#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "llvm-ir-gen/Visitor.h"

int main() {
    ifstream input("testfile.txt");
    ofstream output("output.txt"), llvmFile("llvm.txt"), mipsFile("mips.txt"), errorFile("error.txt");
    Lexer lexer(&input);
    Parser parser(lexer.getLexerList(), &errorFile);
    Visitor visitor(parser.getSyntaxTreeRoot(), &errorFile);
    visitor.getManager()->dumpLlvm(&llvmFile);
    visitor.getManager()->dumpMips(&mipsFile);
    return 0;
}
