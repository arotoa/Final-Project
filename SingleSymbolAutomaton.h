#ifndef SINGLESYMBOLAUTOMATON_H
#define SINGLESYMBOLAUTOMATON_H

#include "Automaton.h"

class SingleSymbolAutomaton : public Automaton
{
public:
    SingleSymbolAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif
