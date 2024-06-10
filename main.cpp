#include <chrono>
#include <iostream>
#include <random>
#include "Graph.h"
#include "solver.h"

int generateRandomNumber(int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, max);
    return dis(gen);
}

Graph getRandGraph(int numNodes, int avgDegree, int maxNumFinal)
{
    std::vector<int> finalStates(maxNumFinal);
    for(int i = 0; i < maxNumFinal; i++)
        finalStates.push_back(generateRandomNumber(numNodes));

    Graph g = Graph(numNodes, finalStates);
    // Initialize the graph with a small seed graph (e.g., a triangle)
    g.addNode(0, 1);
    for (int i = 1; i < avgDegree; i++)
    {
        int owner = 2 - generateRandomNumber(1);
        g.addNode(i, owner);
        g.addEdge(0, i);
    }

    for(int i = avgDegree; i < numNodes; i++)
    {
        // Add nodes with random owner/priority
        int owner = 2 - generateRandomNumber(1);
        g.addNode(i, owner);
        // Randomly add avgDegree outgoing edges to already existing nodes
        for(int j = 0; j < avgDegree; j++)
        {
            int dest = generateRandomNumber(i);
            g.addEdge(i, dest);
        }
    }

    return g;
}

int main()
{
    int numNodes = 1'000'000;
    Graph g("graphs/1mil_nodes.graph");
//    Graph g = getRandGraph(numNodes, 2, 1);
//    g.save("graphs/1mil_nodes.graph");

    auto start = std::chrono::steady_clock::now();
    std::vector<int> attractor = attr(g, g.getFinalStates());
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    std::cout << attractor.size() << std::endl;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return 0;
}