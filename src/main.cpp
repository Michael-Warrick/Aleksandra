#include <iostream>
#include "lexer.hpp"
#include "fileLoader.hpp"

int main(int argc, char* argv[]) 
{
    std::string rawCode = FileLoader::LoadFromFile(argv[1]);

    Lexer lexer = Lexer(rawCode);
    lexer.PrintTokens();

    return 0;
}