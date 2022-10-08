#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input){
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    lineIndex = newLines;
    if (input[index] == '|') {
        index++;
        inputRead++;
        S2(input);
    }

    else {
        index++;
        inputRead++;
        S3(input);
    }
}

void CommentAutomaton::S2(const std::string& input) {
    int tempInt = input.size();
    while (index < tempInt) {
        if (input[index] == '|') {
            index++;
            inputRead++;
            if (input[index] == '#') {
                newLines -= lineIndex;
                inputRead++;
                type = TokenType::COMMENT;
                break;
            }
        }
        else if (input[index] == '\n'){
            newLines++;
            index++;
            inputRead++;
        }
        else {
            index++;
            inputRead++;
        }
    }
}

void CommentAutomaton::S3(const std::string& input) {
    while (input[index] != '\n'){
        index++;
        inputRead++;
    }
    type = TokenType::COMMENT;
}

