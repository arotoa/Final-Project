#include "Graph.h"
#include <sstream>
#include <iostream>

void Graph::dfsForest() {
    for (auto const& n : allNodes){
        if (!n.second.visited){
            dfs(n.second);
        }
    }
}

std::vector<std::set<int>> Graph::dfsForestSCC() {
    while (postOrder.size() != 0){
        if (!allNodes.at(postOrder.top()).visited){
            dfsSCC(allNodes.at(postOrder.top()));
            allSCC.push_back(SCCIds);
            SCCIds.clear();
        }
        postOrder.pop();
    }
    return allSCC;
}

void Graph::dfs(Node thisNode) {
    for (auto const& n : thisNode.dependencies) {
        if (!allNodes.at(n).visited) {
            allNodes.at(n).visited = true;
            dfs(allNodes.at(n));
        }
    }
    postOrder.push(thisNode.id);
    return;
}

void Graph::dfsSCC(Node thisNode) {
    if (!thisNode.visited) {
        allNodes.at(thisNode.id).visited = true;
        SCCIds.emplace(thisNode.id);
        for (auto const& n: thisNode.dependencies) {
            if (!allNodes.at(n).visited) {
                dfsSCC(allNodes.at(n));
            }
        }
    }
    return;
}

std::string Graph::toString() {
    std::ostringstream out;
    for (auto const& n : allNodes){
        out << "R" << n.first << ":";
        for(auto it = n.second.dependencies.begin() ; it != n.second.dependencies.end() ; ++it) {
            if(it != n.second.dependencies.begin())
                out << ",";
            out << "R" << *it;
        }
        out << std::endl;
    }
    return out.str();
}
