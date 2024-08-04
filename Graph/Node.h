#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>
#include <string>
#include "../Environments/Multiagent_Gymnasium/Multiagent_State.h"

class Node
{
public:
    // Constructor
    Node();
    Node(int owner, Multiagent_State state_info);
    // Data
    int owner;
    std::vector<int> out_neighbors;
    std::vector<int> in_neighbors;
    std::map<int, std::string> action_map;
    Multiagent_State state_info;
};

#endif //NODE_H
