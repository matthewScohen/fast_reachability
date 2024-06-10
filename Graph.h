#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <string>

class Graph
{
private:
    int size;
    std::vector<Node> nodes;
public:
    Graph(int size);
    Graph(std::string filepath);
    void save(std::string filepath);

    Node getNode(int node);
    void addNode(int node, int owner);
    void addEdge(int origin, int destination);
    int getSize();
};

#endif //GRAPH_H
