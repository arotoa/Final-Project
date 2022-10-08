#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    int lineNumber = 1;


public:
    Lexer(std::string& input);
    ~Lexer();

    void CreateAutomata();
    void run(std::string& input);
    std::vector<Token*> getTokens ();


};

#endif

