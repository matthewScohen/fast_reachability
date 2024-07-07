#ifndef FAST_REACHABILITY_MULTIAGENT_ENV_H
#define FAST_REACHABILITY_MULTIAGENT_ENV_H

#include "Multiagent_State.h"
#include "../../Graph/Graph.h"
#include <vector>
#include <unordered_map>
#include <map>


enum Action {left, right, move, forward, done};

class Multiagent_Env {
private:
    int width, height, num_agents_t1, num_agents_t2;
    std::vector<std::tuple<int, int>> winning_cells; // The cells that cause team1 to win the game if visited
    std::vector<Multiagent_State> final_states;
    std::vector<Multiagent_State> states;
    Graph game_graph;

    // Maps used to translate between integer nodes in a graph and the corresponding Multiagent_State
    std::vector<Multiagent_State> node_2_state;
    std::map<Multiagent_State, int> state_2_node;

    void generateActions(std::vector<Action>& currentCombo, int n, std::vector<std::vector<Action>>& allCombos);
    void generate_poses(int num_agents, std::vector<std::vector<std::tuple<int, int, int>>>& all_poses);
    std::vector<Multiagent_State> generate_states();
    Graph generate_game_graph();
public:
    Multiagent_State get_transition(Multiagent_State state, std::vector<Action> actions);
    Multiagent_Env(int width, int height, int num_agents_t1, int num_agents_t2, std::vector<std::tuple<int, int>> winning_cells);
};
#endif //FAST_REACHABILITY_MULTIAGENT_ENV_H
