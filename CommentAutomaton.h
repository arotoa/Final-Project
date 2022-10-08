#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H


#include "Automaton.h"

class CommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    int lineIndex;

public:
    CommentAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif
