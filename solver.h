#ifndef SOLVER_H
#define SOLVER_H

#include "Graph/Graph.h"

std::tuple<std::vector<int>, std::map<std::string, std::string>> attr(Graph& graph, const std::vector<int>& finalStates, int reachabilityPlayer);
std::tuple<std::vector<int>, std::map<std::string, std::string>> attr(Graph& graph, const std::vector<int>& finalStates);

#endif //SOLVER_H
