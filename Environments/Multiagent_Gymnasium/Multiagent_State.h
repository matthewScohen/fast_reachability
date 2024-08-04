#ifndef FAST_REACHABILITY_MULTIAGENT_STATE_H
#define FAST_REACHABILITY_MULTIAGENT_STATE_H

#include <vector>
#include <tuple>

class Multiagent_State {
public:
    Multiagent_State(std::vector<std::tuple<int, int, int>> team1_poses, std::vector<std::tuple<int, int, int>> team2_poses, int turn);
    Multiagent_State();
    std::string get_string_representation();
    bool operator==(const Multiagent_State& other) const;
    bool operator<(const Multiagent_State& other) const;
    // Turn is an int indicating the team who takes an action at this state
    int turn;
    // Poses contain the positions and direction data for each member of the team in the form (x,y,rot) where
    // rot is 0,1,2,3 for N,E,S,W
    std::vector<std::tuple<int, int, int>> team1_poses;
    std::vector<std::tuple<int, int, int>> team2_poses;
};

#endif //FAST_REACHABILITY_MULTIAGENT_STATE_H
