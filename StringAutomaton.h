#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H


#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    int lineIndex;

public:
    StringAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif
