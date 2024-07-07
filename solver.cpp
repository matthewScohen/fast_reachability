#include <vector>
#include "solver.h"
#include "Graph/Graph.h"

std::vector<int> attr(Graph& graph, std::vector<int> finalStates)
{
    return attr(graph, finalStates, 1);
}

std::vector<int> attr(Graph& graph, std::vector<int> finalStates, int reachabilityPlayer)
{
    // reachabilityPlayer is the player with a reachability objective for the game
    // State map tracks the number of edges that must be eliminated to add a state to the attractor
    // If 0 edges need to be eliminated it can be added to the attractor
    std::vector<int> stateMap(graph.getSize(), -1);
    std::vector<int> attractor;
    // Set initial final states to 0 in map
    for (const int s : finalStates)
    {
        stateMap[s] = 0;
        attractor.push_back(s);
    }
    int index = 0;
    while(index < attractor.size())
    {
        // Iterate over all states s with edges going to attractor[index]
        for(const int s : graph.getNode(attractor[index]).in_neighbors)
        {
            // if state has not been reached before
            if(stateMap[s] == -1)
            {
                if(graph.getNode(s).owner == reachabilityPlayer)
                {
                    attractor.push_back(s);
                    stateMap[s] = 0;
                }
                else
                {
                    // The number of edges that must be eliminated from s to add it to the attractor are all of its
                    // outgoing edges, we subtract 1 to eliminate the current state
                    stateMap[s] = graph.getNode(s).out_neighbors.size() - 1;
                    if(stateMap[s] == 0)
                        attractor.push_back(s);
                }
            }
            // if the state belongs to the safety player and has edges left to be eliminated
            else if(graph.getNode(s).owner != reachabilityPlayer && stateMap[s] > 0)
            {
                // eliminate the edge
                stateMap[s]--;
                // if there are no more edges to eliminate add the state to the attractor
                if(stateMap[s] == 0)
                    attractor.push_back(s);
            }
        }
        index++;
    }
    return attractor;
}