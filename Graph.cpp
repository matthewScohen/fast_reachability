#include "Graph.h"

Graph::Graph(int size)
{
    this->nodes = std::vector<Node>(size);
    this->size = size;
}

Graph::Graph(std::string filepath)
{
    // TODO load file filepath
    // CSV edge list format where 1st line gives number of nodes
}

void Graph::save(std::string filepath)
{
    // TODO save to file
}

Node Graph::getNode(int node)
{
    return this->nodes[node];
}

void Graph::addNode(int node, int owner)
{
    this->nodes[node].owner = owner;
}

void Graph::addEdge(int from, int to)
{
    this->nodes[from].out_neighbors.push_back(to);
    this->nodes[to].in_neighbors.push_back(from);
}

int Graph::getSize()
{
    return this->size;
}
