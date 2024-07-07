#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
public:
    // Constructor
    Node();
    Node(int owner);
    // Data
    int owner;
    std::vector<int> out_neighbors;
    std::vector<int> in_neighbors;
};

#endif //NODE_H
