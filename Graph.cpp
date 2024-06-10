#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include "Graph.h"

Graph::Graph(int size, std::vector<int> finalStates)
{
    this->nodes = std::vector<Node>(size);
    this->finalStates = std::move(finalStates);
    this->size = size;
}

Graph::Graph(const std::string& filepath)
{
    std::ifstream inFile(filepath);
    if (!inFile.is_open())
        throw std::runtime_error("failed to open file");

    std::string line;
    // parse the graph size
    std::getline(inFile, line);
    this->size = std::stoi(line);
    this->nodes = std::vector<Node>(this->size);

    // Parse the final states
    std::getline(inFile, line);
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ','))
        finalStates.push_back(std::stoi(token));

    // parse the other nodes and edges
    while (std::getline(inFile, line))
    {

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while(std::getline(ss, token, ','))
        {
            tokens.push_back(token);
        }

        if (tokens.size() < 2)
            throw std::invalid_argument( "read invalid line format" );

        int nodeNum = std::stoi(tokens[0]);
        int owner = std::stoi(tokens[1]);

        this->addNode(nodeNum, owner);
        for (std::size_t i = 2; i < tokens.size(); ++i)
        {
            int out_neighbor = std::stoi(tokens[i]);
            addEdge(nodeNum, out_neighbor);
        }
    }
    inFile.close();
}

int Graph::save(const std::string& filepath)
{
    // Format of file:
    // First line is the graph size
    // Second line is all final states separated by commas
    // Each after line represents the data for 1 node
    // node_number,owner,out_neighbor1,out_neighbor2,out_neighborN
    std::ofstream outFile(filepath);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return 1; // return an error code
    }

    // write graph size
    outFile << this->size << "\n";
    // write first final state
    outFile << this->finalStates[0];
    // write the rest of the final states with a comma in front
    for (std::size_t i = 1; i < this->finalStates.size(); i++)
    {
        outFile << "," << this->finalStates[i];
    }
    outFile << "\n";
    // write all states and edges
    for (std::size_t i = 0; i < this->nodes.size(); i++)
    {
        // write node number
        outFile << i;
        // write node owner
        outFile << "," << this->nodes[i].owner;
        // write node out_neighbors
        if(!this->nodes[i].out_neighbors.empty())
            for(std::size_t j = 0; j < this->nodes[i].out_neighbors.size(); j++)
                outFile << "," << this->nodes[i].out_neighbors[j];
        outFile << "\n";
    }
    outFile.close();
    return 0;
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

void Graph::addFinalState(int node)
{
    this->finalStates.push_back(node);
}

std::vector<int> Graph::getFinalStates()
{
    return this->finalStates;
}

int Graph::getSize()
{
    return this->size;
}
