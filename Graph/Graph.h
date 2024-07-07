#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <string>

class Graph
{
private:
    int size;
    std::vector<int> finalStates;
    std::vector<Node> nodes;
public:
    Graph();
    Graph(int size, std::vector<int> finalStates);
    Graph(const std::string& filepath);
    int save(const std::string& filepath);

    void setSize(int size);
    Node getNode(int node);
    void addNode(int node, int owner);
    void addEdge(int origin, int destination);
    void addFinalState(int node);
    std::vector<int> getFinalStates();
    int getSize();
};

#endif //GRAPH_H
