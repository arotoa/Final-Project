#include "Relation.h"
#include <sstream>

void Relation::addTuple(Tuple newTuple) {
    tuples.emplace(newTuple);
}

Relation* Relation::selectIndexes(std::string newString, int headerIndex) {
    Relation* newRelation = new Relation(relationName, header);
    for (Tuple t : tuples){
        if(newString == t.getValue(headerIndex)){
            if (!newRelation->isFound(t)) {
                newRelation->tuples.emplace(t);
            }
        }
    }
    return newRelation;
}

Relation* Relation::selectValues(std::string newString, int headerIndex) {
    Relation* newRelation = new Relation(relationName, header);
    variableIndexes.push_back(newString);
    newRelation->variableIndexes = variableIndexes;
    int vectorSize = newRelation->variableIndexes.size();
    if (vectorSize == 1) {
        for (const Tuple& t: tuples) {
            newRelation->tuples.emplace(t);
        }
    }

    else{
        bool variableIsFound = false;
        std::vector<int> indexWhereFound;
        for (int i = 0; i < vectorSize - 1; i++) {
            if (variableIndexes.at(i) == newString) {
                variableIsFound = true;
                indexWhereFound.push_back(i);
            }
        }

        if (!variableIsFound){
            for (const Tuple& t : tuples){
                if (!newRelation->isFound(t)) {
                    newRelation->tuples.emplace(t);
                }
            }
        }

        else {
            vectorSize = indexWhereFound.size();
            int index;
            for (int i = 0; i < vectorSize; i++){
                index = indexWhereFound.at(i);
                for (Tuple t : tuples){
                    if (!newRelation->isFound(t)) {
                        if (t.getValue(index) == t.getValue(headerIndex)) {
                            newRelation->tuples.emplace(t);
                        }
                    }
                }
            }
        }
    }
    return newRelation;
}

Relation* Relation::project(std::vector<int> variableIndices, std::vector<std::string> variableNames){ //#TODO project problem with changing variables
    Relation* newRelation = new Relation(relationName, header);
    int vectorSize = variableIndices.size();
    int tempInt = variableNames.size();
    bool isFound;
    std::set<Tuple> newTuples;
    Header newHeader;
    for (int i = 0; i < vectorSize; i++){
        isFound = false;
        for (int j = 0; j < tempInt; j++){
            if (j > i){
                if(variableNames.at(i) == variableNames.at(j)){
                    isFound = true;
                    variableNames.erase(variableNames.begin() + j);
                    tempInt--;
                }
            }
        }
        if (!isFound) {
            newHeader.addAttribute(header.getHeader(variableIndices.at(i)));
        }

    }
    newRelation->header = newHeader;
    for (Tuple t : tuples){
        Tuple newTuple;
        for (int i = 0; i < vectorSize; i++){
            newTuple.addValue(t.getValue(variableIndices.at(i)));
        }
            newTuples.emplace(newTuple);
    }
    newRelation->tuples = newTuples;
    return newRelation;
}

Relation *Relation::join(Relation* relation) {
    Header newHeader = header;
    std::vector<int> indexFirstRelation;
    std::vector<int> indexSecondRelation;
    int headerSizeOne = header.getAmountOfAttributes();
    int headerSizeTwo = relation->header.getAmountOfAttributes();
    for (int i = 0; i < headerSizeOne; i++){
        for (int j = 0; j < headerSizeTwo; j++) {
            if (newHeader.getHeader(i) != relation->header.getHeader(j)) {
                if (!newHeader.isFound(relation->header.getHeader(j))) {
                    newHeader.addAttribute(relation->header.getHeader(j));
                }
            }
            else {
                indexFirstRelation.push_back(i);
                indexSecondRelation.push_back(j);
            }
        }
    }

    Relation* newRelation = new Relation(relationName, newHeader);
    std::set<Tuple> newTuples;
    bool alreadyThere;
    int vectorSize;
    int secondVectorSize;
    headerSizeOne = indexFirstRelation.size();
    bool canJoin;
    for (const Tuple& s : relation->tuples) {
        for (const Tuple&  t : tuples) {
            canJoin = true;
            for (int i = 0; i < headerSizeOne; i++) {
                if (t.values.at(indexFirstRelation.at(i)) != s.values.at(indexSecondRelation.at(i))){
                    canJoin = false;
                    break;
                }
            }
            if (canJoin){
                //join tuples
                Tuple newTuple;
                newTuple = t;
                vectorSize = s.values.size();
                secondVectorSize = indexSecondRelation.size();
                for (int i = 0; i < vectorSize; i++){
                    alreadyThere = false;
                    for (int j = 0; j < secondVectorSize; j++){
                        if (i == indexSecondRelation.at(j)){
                            alreadyThere = true;
                            break;
                        }
                    }
                    if (!alreadyThere){
                        newTuple.values.push_back(s.values.at(i));
                    }
                }
                newTuples.emplace(newTuple);
            }
        }
    }
    newRelation->tuples = newTuples;
    return newRelation;
}

Relation* Relation::rename(std::vector<std::string> variableNames) {
    Relation* newRelation = new Relation(relationName, header);
    std::vector<int> newVariableIndices;
    Header newHeader;
    int vectorSize = variableNames.size();
    std::set<Tuple> newTuples;
    for (int i = 0; i < vectorSize; i++){
        if (!newHeader.isFound(variableNames.at(i))) {
            newVariableIndices.push_back(i);
            newHeader.addAttribute(variableNames.at(i));
        }
    }
    newRelation->header = newHeader;
    vectorSize = newVariableIndices.size();
    for (Tuple t : tuples){
        Tuple newTuple;
        for (int i = 0; i < vectorSize; i++) {
            newTuple.addValue(t.getValue(newVariableIndices[i]));
        }
        newTuples.emplace(newTuple);
    }
    newRelation->tuples = newTuples;
    return newRelation;
}

std::string Relation::toString() {
    std::ostringstream out;
    int vectorSize;
    int outputCount = 0;
    for (Tuple t : tuples){
        vectorSize = header.getAmountOfAttributes();
        for (int i = 0; i < vectorSize; i++){
            if (header.getHeader(i)[0] != '\'') {
                if (outputCount != 0){
                    out << ", ";
                }
                else {
                    out << "  ";
                }
                out << header.getHeader(i) << "=" << t.getValue(i);
                outputCount++;
            }
        }
        if (outputCount!= 0){
            out << std::endl;
        }
        outputCount = 0;
    }
    return out.str();
}

void Relation::clearVector() {
    variableIndexes.clear();
}

bool Relation::isFound(Tuple findTuple) {
    int vectorSize;
    bool isInTuple = false;
    for (Tuple t : tuples){
        vectorSize = t.getVectorSize();
        for (int i = 0; i < vectorSize; i++){
            if (t.getValue(i) == findTuple.getValue(i)){
                isInTuple = true;
            }
            else {
                isInTuple = false;
                break;
            }
        }
        if (isInTuple){
            return true;
        }
    }
    return false;
}

void Relation::addManyTuples(Relation *anotherRelation) {
    for(const Tuple& t : anotherRelation->tuples){
        if(tuples.insert(t).second){
            std::cout << printOneTuple(t);
            addedTuple = true;
        }
    }
}

std::string Relation::printOneTuple(Tuple t) {
    std::ostringstream out;
    int vectorSize;
    int outputCount = 0;
    vectorSize = header.getAmountOfAttributes();
    for (int i = 0; i < vectorSize; i++) {
        if (header.getHeader(i)[0] != '\'') {
            if (outputCount != 0) {
                out << ", ";
            } else {
                out << "  ";
            }
            out << header.getHeader(i) << "=" << t.getValue(i);
            outputCount++;
        }
    }
    if (outputCount!= 0) {
        out << std::endl;
    }
    return out.str();
}
