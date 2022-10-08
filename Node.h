#ifndef NODE_H
#define NODE_H
#include <set>

class Node {
public:
    Node(){ visited = false;}
    int id;
    std::set<int>dependencies;
    bool visited;

};

#endif