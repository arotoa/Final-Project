#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include <vector>
#include <set>

class Parser {
private:
    std::vector<Token*> tokens;
    TokenType currParsingStage;
    Parameter* parameter;
    Predicate* predicate;
    Rule* rules;
    bool isString = false;

    void match(TokenType correctToken);
    bool predict(TokenType correctToken);
    void parseSchemes();
    void parseFacts();
    void parseRules();
    void parseQueries();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIdList();
    void parseParameter();




public:
    int currIndex;
    Parser(std::vector<Token*> allTokens);
    ~Parser();
    void parse();

    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> allRules;
    std::set<std::string> domains;
};


#endif