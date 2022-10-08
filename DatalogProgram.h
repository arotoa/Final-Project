#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include <vector>
#include <set>
#include "Token.h"
#include "Parser.h"
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram {
private:
    std::vector<Token*> tokens;

public:
    DatalogProgram(std::vector<Token*> allTokens) {tokens = allTokens;}
    ~DatalogProgram() {};
    void startParser();
    std::string toString();
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::set<std::string> domains;


};


#endif
