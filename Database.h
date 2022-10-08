#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include "Relation.h"
#include "Tuple.h"



class Database {
private:
    std::map<std::string, Relation*> dataBase;

public:
    void addRelation(std::string name, Relation* newRelation){
        dataBase.insert(std::pair<std::string, Relation*>(name, newRelation));
    }
    Relation* getRelation(std::string name){
        return dataBase[name];
    }
    void addTupleToRelation(Tuple tuple, std::string name){
        dataBase[name]->addTuple(tuple);
    }

    void changeRelation(std::string name, Relation* newRelation){
        dataBase.erase(name);
        dataBase.insert(std::pair<std::string, Relation*>(name, newRelation));
    }
};


#endif
