#ifndef FAST_REACHABILITY_MULTIAGENT_ENV_H
#define FAST_REACHABILITY_MULTIAGENT_ENV_H

#include "Multiagent_State.h"
#include "../../Graph/Graph.h"
#include <vector>
#include <unordered_map>
#include <map>
#include <string>


enum Action {left, right, forward, done};

class Multiagent_Env {
private:
    int width, height, num_agents_t1, num_agents_t2;
    std::vector<std::tuple<int, int>> winning_cells; // The cells that cause team1 to win the game if visited
    std::vector<Multiagent_State> states;
    std::vector<Multiagent_State> final_states_p1;
    std::vector<Multiagent_State> final_states_p2;

    // Maps used to translate between integer nodes in a graph and the corresponding Multiagent_State
    std::vector<Multiagent_State> node_2_state;
    std::unordered_map<std::string, int> state_2_node;

    bool is_final_state_p1(Multiagent_State state);
    bool is_final_state_p2(Multiagent_State state);
    void generateActions(std::vector<Action>& currentCombo, int n, std::vector<std::vector<Action>>& allCombos);
    void generate_poses(int num_agents, std::vector<std::vector<std::tuple<int, int, int>>>& all_poses);
    std::vector<Multiagent_State> generate_states();
    Graph generate_game_graph();
public:
    Graph game_graph;
    std::vector<int> p2_final_state_indexes;
    Multiagent_State get_transition(Multiagent_State state, std::vector<Action> actions);
    Multiagent_Env(int width, int height, int num_agents_t1, int num_agents_t2, std::vector<std::tuple<int, int>> winning_cells);
};
#endif //FAST_REACHABILITY_MULTIAGENT_ENV_H
