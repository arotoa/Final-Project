#include "Lexer.h"
#include "SingleSymbolAutomaton.h"
#include "ColonDashAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include <iostream>

Lexer::Lexer(std::string& input) {
    CreateAutomata();
    run(input);
}

Lexer::~Lexer() {
}

void Lexer::CreateAutomata() {
    automata.push_back(new SingleSymbolAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
}

void Lexer::run(std::string& input) {
    int maxRead;
    int inputRead;
    int tempInt;
    std::string tempString;
    Automaton * maxAutomaton;

    while (input.size() > 0){

        //reset values of variables
        inputRead = 0;
        maxRead = 0;

        //look for tokens
        tempInt = automata.size();
        for (int i = 0; i < tempInt; i++) {
            inputRead = automata[i]->createToken(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }

        //New line
        if (input[0] == '\n'){
            lineNumber += 1;
        }

        if (maxRead > 0){

            //Undefined for string or comment not ending
            if (input.size() != 1) {
                tempInt = input.size();
            }
            if (maxRead == tempInt){
                tokens.push_back(new Token(TokenType::UNDEFINED, input, lineNumber));
                lineNumber += maxAutomaton->newLinesRead();
                input.erase();
            }

            //Regular Expression
            else {
                if (maxAutomaton->getType() != TokenType::COMMENT) {
                    tokens.push_back(maxAutomaton->createToken(input.substr(0, maxRead), lineNumber));
                }
                input.erase(0, maxRead);
                lineNumber += maxAutomaton->newLinesRead();
            }
        }


        else {
            tempString = input[0];
            if (!std::isspace(input[0]) && input[0] != '\n') {
                tokens.push_back(new Token(TokenType::UNDEFINED, tempString, lineNumber));
            }
            input.erase(0,1);
        }
    }
    tokens.push_back(new Token(TokenType::END, "", lineNumber));
}

std::vector<Token*> Lexer::getTokens() {
    return tokens;
};


