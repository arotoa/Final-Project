#ifndef PARAMETER_H
#define PARAMETER_H
#include <iostream>


class Parameter {
private:
    std::string idOrString;
    bool isConstant;
public:
    Parameter (std::string paraString, bool isString) {
        isConstant = isString;
        idOrString = paraString;
    }
    std::string toString(){
        return idOrString;
    }
    bool isString(){
        return isConstant;
    }
};


#endif
