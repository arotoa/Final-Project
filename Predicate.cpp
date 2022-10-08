#include "Predicate.h"
#include <sstream>


void Predicate::addParameter(Parameter *parameter) {
    parameters.push_back(parameter);
}

std::string Predicate::getID() {
    return id;
}

std::vector<std::string> Predicate::getParameters() {
    int vectorSize = parameters.size();
    std::vector<std::string> parametersAsString;
    for (int i = 0; i < vectorSize; i++){
        parametersAsString.push_back(parameters.at(i)->toString());
    }
    return parametersAsString;
}

Parameter* Predicate::getParameter(int index) {
    return parameters.at(index);
}

std::string Predicate::toString() {
    std::ostringstream out;
    out << id << "(";
    int vectorSize = parameters.size();
    for (int i = 0; i < vectorSize; i++){
        out << parameters.at(i)->toString();
        if (i < vectorSize - 1){
            out << ",";
        }
    }
    out << ")";
    return out.str();
}