#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <stack>
#include <vector>
#include "Node.h"


class Graph {
public:
    std::map<int, Node> allNodes;
    std::stack<int> postOrder;
    std::set<int> SCCIds;
    std::vector<std::set<int>> allSCC;

    void dfsForest();
    std::vector<std::set<int>> dfsForestSCC();
    void dfs(Node thisNode);
    void dfsSCC(Node thisNode);
    std::string toString();
};


#endif //UNTITLED_GRAPH_H
