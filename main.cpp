#include <chrono>
#include <iostream>
#include "Graph.h"
#include "solver.h"

int main()
{
    int numNodes = 3;
    Graph g(numNodes);
    g.addNode(0, 1);
    g.addNode(1, 1);
    g.addNode(2, 0);

    g.addEdge(1, 0);
    g.addEdge(2, 0);
    g.addEdge(2, 2);

    std::vector<int> finalStates;
    finalStates.push_back(0);

    auto start = std::chrono::steady_clock::now();
    std::vector<int> attractor = attr(g, finalStates);
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;

    std::cout << attractor.size() << std::endl;
    std::cout << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return 0;
}