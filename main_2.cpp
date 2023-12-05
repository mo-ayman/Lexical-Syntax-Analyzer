#include "DFASerialization/DFASerialization.h"
#include "LexicalAnalyzer/LexicalAnalyzer.h"
#include <iomanip>
using namespace std;
int main()
{
    std::string src_path = __FILE__;
    src_path = src_path.substr(0, src_path.find_last_of("\\/"));

    LexicalAnalyzer lexer(src_path+"/test_program.txt", 1024, src_path + "/min_dfa.dat");
    Token token;
    do
    {
        token = lexer.getNextToken();
        if (!token.error.empty())
        {
            cout << "Error, removing \"" << token.error << "\"" << endl;
        }
        std::cout << std::setw(8) << "Pos: " << std::setw(5) << token.filePos
                  << " | Type: " << std::setw(10) << token.type
                  << " | Lexeme: \"" << token.lexeme << "\""
                  << std::endl;    } while (token.type != "EOF");
    return 0;
}