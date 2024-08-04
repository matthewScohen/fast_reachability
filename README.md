# Fast Reachability Game Solver
This project is a solver and environment for generating multi-agent games and computing winning strategies on them using
attractor computation. The attractor algorithm is based on the improved Ziolenka's algorithm as described in 
[this paper](https://www.sciencedirect.com/science/article/pii/S1877050917306853).

## Usage
The file Environments/Multiagent_Gymnasium/test.cpp demonstrates how to use the code in this repository. To modify this
project for use with other multi-agent games follow the steps below.


1. Provide a new implementation of MultiagentState.cpp that conforms to the MultiagentState.h header file.
2. Provide appropriate definitions for the following functions in MutliagentEnvironment.cpp

   - is\_final\_state\_p1
   - is\_final\_state\_p2
   - generate\_states
   - get\_transition
