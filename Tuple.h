#ifndef TUPLE_H
#define TUPLE_H
#include <iostream>
#include <vector>

class Tuple {

public:
    std::vector<std::string> values;

    void addValue(std::string value){
        values.push_back(value);
    }
    std::string getValue(int index){
        return values.at(index);
    }
    int getVectorSize(){
        return values.size();
    }

    bool operator< (const Tuple &rhs) const {
        return values < rhs.values;
    }

};


#endif
