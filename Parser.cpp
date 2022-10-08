#include "Parser.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include <sstream>

Parser::Parser(std::vector<Token*> allTokens) {
    tokens = allTokens;
    currIndex = 0;
}

Parser::~Parser() {
}

void Parser::match(TokenType correctToken) {
    if (tokens[currIndex]->getType() != correctToken){
        throw tokens[currIndex];
    }
    else {
        currIndex++;
    }
}
bool Parser::predict(TokenType correctToken) {
    if (tokens[currIndex]->getType() != correctToken){
        return false;
    }
    else {
        return true;
    }
}

void Parser::parse() {

    //Schemes
    match(TokenType::SCHEMES);
    currParsingStage = TokenType::SCHEMES;
    match(TokenType::COLON);
    parseSchemes();
    parseSchemeList();

    //Facts
    match(TokenType::FACTS);
    currParsingStage = TokenType::FACTS;
    match(TokenType::COLON);
    parseFactList();

    //Rules
    match(TokenType::RULES);
    currParsingStage = TokenType::RULES;
    match(TokenType::COLON);
    parseRuleList();

    //Queries
    match(TokenType::QUERIES);
    currParsingStage = TokenType::QUERIES;
    match(TokenType::COLON);
    parseQueries();
    parseQueryList();
}

void Parser::parseSchemes() {
    match(TokenType::ID);
    predicate = new Predicate(tokens[currIndex - 1]->getInfo());
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    parameter = new Parameter(tokens[currIndex - 1]->getInfo(), 0);
    predicate->addParameter(parameter);
    parseIdList();
    match(TokenType::RIGHT_PAREN);
    schemes.push_back(predicate);
}

void Parser::parseFacts() {
    match(TokenType::ID);
    predicate = new Predicate(tokens[currIndex - 1]->getInfo());
    match(TokenType::LEFT_PAREN);
    match(TokenType::STRING);
    domains.emplace(tokens[currIndex - 1]->getInfo());
    parameter = new Parameter(tokens[currIndex - 1]->getInfo(), 1);
    predicate->addParameter(parameter);
    if(!predict(TokenType::RIGHT_PAREN)) {
        parseStringList();
    }
    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);
    facts.push_back(predicate);
}

void Parser::parseRules() {
    parseHeadPredicate();
    match(TokenType::COLON_DASH);
    parsePredicate();
    rules->addPredicate(predicate);
    parsePredicateList();
    match(TokenType::PERIOD);
    allRules.push_back(rules);
}

void Parser::parseQueries() {
    parsePredicate();
    match(TokenType::Q_MARK);
    queries.push_back(predicate);
}

void Parser::parseHeadPredicate() {
    match(TokenType::ID);
    predicate = new Predicate(tokens[currIndex - 1]->getInfo());
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    parameter = new Parameter(tokens[currIndex - 1]->getInfo(), 0);
    predicate->addParameter(parameter);
    parseIdList();
    match(TokenType::RIGHT_PAREN);
    rules = new Rule(predicate);
}

void Parser::parsePredicate() {
    match(TokenType::ID);
    predicate = new Predicate(tokens[currIndex - 1]->getInfo());
    match(TokenType::LEFT_PAREN);
    parseParameter();
    parameter = new Parameter(tokens[currIndex - 1]->getInfo(), isString);
    predicate->addParameter(parameter);
    parseParameterList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parseSchemeList() {
    if (predict(TokenType::ID)){
        parseSchemes();
        parseSchemeList();
    }
}

void Parser::parseFactList() {
    if (predict(TokenType::ID)){
        predicate = new Predicate(tokens[currIndex - 1]->getInfo());
        parseFacts();
        parseFactList();
    }
}

void Parser::parseRuleList() {
    if (predict(TokenType::ID)) {
        parseRules();
        parseRuleList();
    }
}

void Parser::parseQueryList() {
    if (predict(TokenType::ID)) {
        parseQueries();
        parseQueryList();
    }
}

void Parser::parsePredicateList() {
   if (predict(TokenType::COMMA)) {
       match(TokenType::COMMA);
       parsePredicate();
       if (currParsingStage == TokenType::RULES) {
           rules->addPredicate(predicate);
       }
       parsePredicateList();
   }
}

void Parser::parseParameterList() {
    if (predict(TokenType::COMMA)) {
        match(TokenType::COMMA);
        parseParameter();
        parameter = new Parameter(tokens[currIndex - 1]->getInfo(), isString);
        predicate->addParameter(parameter);
        parseParameterList();
    }

}

void Parser::parseStringList() {
    match(TokenType::COMMA);
    match(TokenType::STRING);
    if (currParsingStage == TokenType::FACTS){
        domains.emplace(tokens[currIndex - 1]->getInfo());
    }
    parameter = new Parameter(tokens[currIndex - 1]->getInfo(), 1);
    predicate->addParameter(parameter);
    if (predict(TokenType::COMMA)){
        parseStringList();
    }
}

void Parser::parseIdList() {
    if (predict(TokenType::COMMA)){
        match(TokenType::COMMA);
        match(TokenType::ID);
        parameter = new Parameter(tokens[currIndex - 1]->getInfo(), 0);
        predicate->addParameter(parameter);
        parseIdList();
    }
}

void Parser::parseParameter() {
    if (predict(TokenType::STRING)){
        match(TokenType::STRING);
        isString = true;
    }
    else if (predict(TokenType::ID)){
        match(TokenType::ID);
        isString = false;
    }
}