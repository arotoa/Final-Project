#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Predicate.h"


class Interpreter {
private:
    DatalogProgram* datalogProgram;
    Database database;
    int amountOfParameters;
    std::string relationName;
    std::vector<std::string> stringVector;
    Relation* relation;
    Relation* newRelation;
    bool isEvaluatingRules;

public:
    Interpreter (DatalogProgram* parser);
    ~Interpreter(){}
    void run();
    Relation* evaluatePredicate(Predicate* predicate);
};


#endif
