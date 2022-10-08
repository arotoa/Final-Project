#ifndef PREDICATE_H
#define PREDICATE_H
#include "Token.h"
#include "Parameter.h"
#include <vector>


class Predicate {
private:
    std::string id;
public:
    Predicate(std::string setId) {id = setId;}
    ~Predicate(){}
    void addParameter(Parameter* parameter);
    std::string getID();
    std::vector<std::string> getParameters();
    std::vector<Parameter*> parameters;
    Parameter* getParameter(int index);
    std::string toString();
};


#endif
