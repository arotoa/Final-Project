#include "Interpreter.h"
#include "Relation.h"
#include "Header.h"
#include "Parameter.h"
#include "Graph.h"
#include <sstream>
#include <algorithm>

Interpreter::Interpreter(DatalogProgram *parser) {
    datalogProgram = parser;
    run();
}


void Interpreter::run() {
    int vectorSize = datalogProgram->schemes.size();

    //Run through Schemes
    for (int i = 0; i < vectorSize; i++){
        relationName = datalogProgram->schemes.at(i)->getID();
        stringVector = datalogProgram->schemes.at(i)->getParameters();
        amountOfParameters = stringVector.size();
        Header header;
        for (int j = 0; j < amountOfParameters; j++){
            header.addAttribute(stringVector.at(j));
        }
        relation = new Relation(relationName, header);
        database.addRelation(relationName, relation);
    }

    //Run through Facts
    vectorSize = datalogProgram->facts.size();

    for (int i = 0; i < vectorSize; i++){
        relationName = datalogProgram->facts.at(i)->getID();
        stringVector = datalogProgram->facts.at(i)->getParameters();
        amountOfParameters = stringVector.size();
        Tuple myTuple;
        for (int j = 0; j < amountOfParameters; j++){
            myTuple.addValue(stringVector.at(j));
        }
        database.addTupleToRelation(myTuple, relationName);
    }

    //evaluate rules
    isEvaluatingRules = true;
    std::string rulePredicateName;
    std::vector<Rule*> allRules;
    std::vector<Predicate*> predicates;
    std::vector<Relation*> newRelations;
    std::vector<std::set<int>> allSCC;
    allRules = datalogProgram->rules;
    vectorSize = allRules.size();
    Graph forwardGraph, backwardGraph;
    int sizeOfVector;
    int temporaryInt;
    bool addedTuples;
    int amountOfPasses = 0;
    addedTuples = false;
    for (int i = 0; i < vectorSize; i++) {
        Node newNode;
        newNode.id = i;
        forwardGraph.allNodes.insert(std::pair<int, Node>(i, newNode));
        backwardGraph.allNodes.insert(std::pair<int, Node>(i, newNode));
    }
    for (int i = 0; i < vectorSize; i++) {
        temporaryInt = allRules[i]->bodyPredicates.size();
        for (int j = 0; j < temporaryInt; j++) {
            for (int k = 0; k < vectorSize; k++) {
                if (allRules[i]->bodyPredicates[j]->getID() == allRules[k]->headPredicate->getID()) {
                    forwardGraph.allNodes.at(i).dependencies.emplace(k);
                    backwardGraph.allNodes.at(k).dependencies.emplace(i);
                }
            }
        }
    }
    std::cout << "Dependency Graph\n";
    std::cout << forwardGraph.toString() << std::endl;

    backwardGraph.dfsForest();
    forwardGraph.postOrder = backwardGraph.postOrder;
    allSCC = forwardGraph.dfsForestSCC();



    std::cout << "Rule Evaluation\n";
    vectorSize = allSCC.size();
    std::set<int> tempSet;
    Relation *resultRelation;

    for (int i = 0; i < vectorSize; i++) {
        amountOfPasses = 0;
        tempSet = allSCC.at(i);
        std::ostringstream SCCPrinted;
        std::cout << "SCC: ";
        for(auto it = tempSet.begin() ; it != tempSet.end() ; ++it) {
            if(it != tempSet.begin())
                SCCPrinted << ",";
            SCCPrinted << "R" << *it;
        }
        std::cout << SCCPrinted.str();
        std::cout << std::endl;

        do {
            addedTuples = false;
            for (auto n : tempSet) {
                std::cout << allRules.at(n)->toString();

                //evaluate the right side of rules
                newRelations.clear();
                predicates = allRules.at(n)->bodyPredicates;
                sizeOfVector = predicates.size();
                for (int j = 0; j < sizeOfVector; j++) {
                    rulePredicateName = predicates.at(j)->getID();
                    relation = database.getRelation(rulePredicateName);
                    newRelation = relation;
                    stringVector = predicates.at(j)->getParameters();
                    amountOfParameters = stringVector.size();
                    evaluatePredicate(predicates.at(j));
                    newRelations.push_back(newRelation);
                    if (j != 0) {
                        resultRelation = resultRelation->join(newRelations.at(j));
                    } else {
                        resultRelation = newRelations.at(j);
                    }
                }
                //std::cout << "--------After Join\n" << resultRelation->toString() << "--------\n";

                //project columns from head predicate
                sizeOfVector = resultRelation->header.getAmountOfAttributes();
                std::vector<int> variableIndexes;
                std::vector<std::string> variableNames;
                Predicate *predicate = allRules.at(n)->headPredicate;
                Header newHeader;
                int tempInt = predicate->parameters.size();
                for (int l = 0; l < tempInt; l++) {
                    newHeader.addAttribute(predicate->parameters.at(l)->toString());
                }
                Relation *testRelation = new Relation(predicate->getID(), newHeader);
                tempInt = newHeader.getAmountOfAttributes();
                for (int j = 0; j < tempInt; j++) {
                    for (int k = 0; k < sizeOfVector; k++) {
                        if (testRelation->header.getHeader(j) == resultRelation->header.getHeader(k)) {
                            variableIndexes.push_back(k);
                            variableNames.push_back(resultRelation->header.getHeader(k));
                        }
                    }
                }
                resultRelation = resultRelation->project(variableIndexes, variableNames);

                //rename relation
                testRelation = database.getRelation(allRules.at(n)->headPredicate->getID());
                resultRelation->header = testRelation->header;
                resultRelation->relationName = testRelation->relationName;

                testRelation->addedTuple = false;
                testRelation->addManyTuples(resultRelation);
                if (testRelation->addedTuple) {
                    addedTuples = true;
                }
                database.changeRelation(testRelation->relationName, testRelation);
                if (tempSet.size() == 1 && !allRules.at(n)->findPredicate(testRelation->relationName)){
                    addedTuples = false;
                }
            }
            amountOfPasses++;
        } while (addedTuples);
        std::cout << amountOfPasses << " passes: " << SCCPrinted.str() << std::endl;
    }


    //evaluate queries
    isEvaluatingRules = false;
    std::cout << "\nQuery Evaluation\n";
   std::string queryPredicateName;
    std::vector<Predicate*> allQueries;
    allQueries = datalogProgram->queries;
    vectorSize = allQueries.size();
    for (int i = 0; i < vectorSize; i++){
        queryPredicateName = allQueries.at(i)->getID();
        relation = database.getRelation(queryPredicateName);
        newRelation = relation;
       stringVector = allQueries.at(i)->getParameters();
       amountOfParameters = stringVector.size();
       evaluatePredicate(allQueries.at(i));
    }
}


Relation* Interpreter::evaluatePredicate(Predicate* predicate){
    Header newHeader;
    Parameter* indexParameter;
    std::vector<int> variableIndexes;
    std::vector<std::string> variableNames;
    for (int i = 0; i < amountOfParameters; i++){
        indexParameter = predicate->getParameter(i);
        if(indexParameter->isString()){
            newRelation = newRelation->selectIndexes(stringVector.at(i), i);
        }
        else {
            variableIndexes.push_back(i);
            variableNames.push_back(stringVector.at(i));
            newRelation = newRelation->selectValues(stringVector.at(i), i);
        }
    }
    newRelation = newRelation->project(variableIndexes, variableNames);
    newRelation = newRelation->rename(variableNames);
    relation->clearVector();

    //Print query and new relation
    if(!isEvaluatingRules) {
        int numOfTuples = newRelation->getRelationSize();
        std::cout << predicate->toString() << "?";
        if (numOfTuples != 0) {
            std::cout << " Yes(" << numOfTuples << ")\n";
        } else {
            std::cout << " No\n";
        }
        std::cout << newRelation->toString();
    }
    return new Relation(predicate->getID(), newHeader);
}

