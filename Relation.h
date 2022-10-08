#ifndef RELATION_H
#define RELATION_H
#include "Tuple.h"
#include "Header.h"
#include <set>
#include <map>
#include <vector>

class Relation {
public:
    Relation (std::string name, Header setHeader) {relationName = name; header = setHeader;}
    ~Relation(){}

    std::vector<std::string> variableIndexes;
    std::set<Tuple> tuples;
    std::string relationName;

    Relation* selectIndexes(std::string newString, int headerIndex);
    Relation* selectValues(std::string newString, int headerIndex);
    Relation* project(std::vector<int> variableIndices, std::vector<std::string> variableNames);
    Relation* join(Relation* relation);
    Relation* rename(std::vector<std::string> variableNames);
    void addTuple(Tuple newTuple);
    void addManyTuples(Relation* anotherRelation);
    std::string toString();
    void clearVector();
    bool isFound(Tuple findTuple);
    int getRelationSize(){ return tuples.size(); }
    Header header;
    std::string printOneTuple(Tuple t);
    bool addedTuple;


};


#endif
