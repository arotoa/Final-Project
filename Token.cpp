#include "Token.h"
#include <sstream>

Token::Token(TokenType type, std::string description, int line) {
    tokenType = type;
    info = description;
    lineNum = line;
}

std::string Token::getTypeInString(){
    switch(tokenType) {
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::PERIOD:
            return "PERIOD";
        case TokenType::Q_MARK:
            return "Q_MARK";
        case TokenType::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenType::COLON:
            return "COLON";
        case TokenType::COLON_DASH:
            return "COLON_DASH";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::ADD:
            return "ADD";
        case TokenType::SCHEMES:
            return "SCHEMES";
        case TokenType::FACTS:
            return "FACTS";
        case TokenType::RULES:
            return "RULES";
        case TokenType::QUERIES:
            return "QUERIES";
        case TokenType::ID:
            return "ID";
        case TokenType::STRING:
            return "STRING";
        case TokenType::COMMENT:
            return "COMMENT";
        case TokenType::UNDEFINED:
            return "UNDEFINED";
        case TokenType::END:
            return "EOF";
        default:
            return "";
    }
}


std::string Token::toString() {
    std::ostringstream out;
    out << '(' << getTypeInString();
    out << ",\"" << info;
    out << "\"," << lineNum << ')';
    return out.str();
}

TokenType Token::getType() {
    return tokenType;
}

std::string Token::getInfo(){
    return info;
}