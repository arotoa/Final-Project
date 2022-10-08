#include "Rule.h"
#include <sstream>

std::string Rule::toString() {
    std::ostringstream out;
    out << headPredicate->toString() << " :- ";
    int vectorSize = bodyPredicates.size();
    for (int i = 0; i < vectorSize; i++){
        out << bodyPredicates.at(i)->toString();
        if (i == vectorSize - 1){
            out << ".\n";
        }
        else{
            out << ",";
        }
    }
    return out.str();
}

bool Rule::findPredicate(std::string &name) {
    bool isFound = false;
    for (unsigned int i = 0; i < bodyPredicates.size(); i++){
        if (bodyPredicates.at(i)->getID() == name){
            isFound = true;
        }
    }
    return isFound;
}