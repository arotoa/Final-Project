#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "DatalogProgram.h"
#include "Interpreter.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }

    // open file
    std::string fileName = argv[1];
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cout << "File " << fileName << " could not be found or opened." << std::endl;
        return 1;
    }
    std::string input(std::istreambuf_iterator<char>(inputFile), {});

    Lexer* lexer = new Lexer(input);

    DatalogProgram* parser = new DatalogProgram(lexer->getTokens());
    try {
        parser->startParser();
    }
    catch (Token* error){
        std::cout << "Failure!\n" << "  " << error->toString() << std::endl;
    }

    Interpreter* database = new Interpreter(parser);


    delete lexer;
    delete parser;
    delete database;

    return 0;
}