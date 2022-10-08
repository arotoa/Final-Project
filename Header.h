#ifndef HEADER_H
#define HEADER_H
#include <vector>
#include <iostream>


class Header {
private:
    std::vector<std::string> attributes;
public:
    Header(){}
    void addAttribute(std::string newAttribute){
        attributes.push_back(newAttribute);
    }
    std::string getHeader(int index){
        return attributes.at(index);
    }
    bool isFound(std::string findString){
        int vectorSize = attributes.size();
        for (int i = 0; i < vectorSize; i++){
            if (findString == attributes.at(i)){ return true;}
        }
        return false;
    }
    int getAmountOfAttributes(){
        return attributes.size();
    }
};


#endif
