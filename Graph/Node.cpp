#include "Node.h"
#include <utility>

Node::Node()
{
    this->owner = -1;
    this->state_info = Multiagent_State();
    this->action_map = std::map<int, std::string>();
}

Node::Node(int owner, Multiagent_State state_info) {
    this->owner = owner;
    this->state_info = std::move(state_info);
    this->action_map = std::map<int, std::string>();
}