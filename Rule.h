#ifndef RULE_H
#define RULE_H
#include "Predicate.h"
#include <vector>


class Rule {
public:
    Rule(Predicate* inPredicate) {headPredicate = inPredicate;}
    void addPredicate(Predicate* predicate){bodyPredicates.push_back(predicate);}
    std::string toString();
    std::vector<Predicate*> bodyPredicates;
    Predicate* headPredicate;
    bool findPredicate(std::string &name);
};


#endif
