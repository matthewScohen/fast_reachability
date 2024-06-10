#include "Node.h"

Node::Node()
{
    this->owner = -1;
}

Node::Node(int owner)
{
    this->owner = owner;
}