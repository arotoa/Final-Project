#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input){
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input){
    lineIndex = newLines;
    int tempInt = input.size();
    if (index == tempInt){}

    else if (input[index] == '\''){
        inputRead++;
        index++;
        S2(input);
    }

    else if(input[index] == '\n'){
        newLines++;
        index++;
        inputRead++;
        S1(input);
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\''){
        index++;
        inputRead++;
        S1(input);
    }
    else {
        //newLines -= lineIndex;
        type = TokenType::STRING;
    }
}

