#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H


#include "Automaton.h"

class IDAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IDAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif
