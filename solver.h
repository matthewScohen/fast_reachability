#ifndef SOLVER_H
#define SOLVER_H

#include "Graph.h"

std::vector<int> attr(Graph& graph, std::vector<int> finalStates, int reachabilityPlayer);
std::vector<int> attr(Graph& graph, std::vector<int> finalStates);

#endif //SOLVER_H
