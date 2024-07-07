#include <iostream>
#include <functional>
#include "Multiagent_Env.h"
#include "../../Graph/Graph.h"
const int NUM_ACTIONS = 5;

Multiagent_Env::Multiagent_Env(int width, int height, int num_agents_t1, int num_agents_t2, std::vector<std::tuple<int, int>> winning_cells) {
    this->width = width;
    this->height = height;
    this->winning_cells = winning_cells;
    this->num_agents_t1 = num_agents_t1;
    this->num_agents_t2 = num_agents_t2;

    this->node_2_state = std::vector<Multiagent_State>();
    this->state_2_node = std::map<Multiagent_State, int>();

    this->final_states = std::vector<Multiagent_State>(); // final_states is populated by generate_states()
    this->states = this->generate_states();
    this->game_graph = this->generate_game_graph();
}

void Multiagent_Env::generate_poses(int num_agents, std::vector<std::vector<std::tuple<int, int, int>>> &all_poses) {
    std::vector<std::tuple<int, int, int>> poses(num_agents);
    std::function<void(int)> generate = [&](int agent)
    {
        if (agent == num_agents) {
            all_poses.push_back(poses);
            return;
        }
        for (int x = 0; x < this->width; x++) {
            for (int y = 0; y < this->height; y++) {
                for (int rot = 0; rot < 4; rot++) {
                    poses[agent] = std::make_tuple(x, y, rot);
                    generate(agent + 1);
                }
            }
        }
    };
    generate(0);
}

void Multiagent_Env::generateActions(std::vector<Action>& currentCombo, int n, std::vector<std::vector<Action>>& allCombos) {
    // Base case: if currentCombo has reached length n, store it in allCombos
    if (currentCombo.size() == n) {
        allCombos.push_back(currentCombo);
        return;
    }

    // Recursive case: add each action to currentCombo and recurse
    for (int i = 0; i < NUM_ACTIONS; ++i) {
        currentCombo.push_back(static_cast<Action>(i));
        this->generateActions(currentCombo, n, allCombos);
        currentCombo.pop_back();
    }
}

std::vector<Multiagent_State> Multiagent_Env::generate_states() {
    // vector containing all possible poses for team1: team1_poses[pose_instance][player_number] = pose
    std::vector<std::vector<std::tuple<int, int, int>>> team1_poses;
    std::vector<std::vector<std::tuple<int, int, int>>> team2_poses;

    generate_poses(this->num_agents_t1, team1_poses);
    generate_poses(this->num_agents_t2, team2_poses);

    std::vector<Multiagent_State> all_states;
    for (const auto& t1_pose : team1_poses) {
        for (const auto& t2_pose : team2_poses) {
            for (int turn = 1; turn <= 2; turn++) {
                Multiagent_State state;
                state.team1_poses = t1_pose;
                state.team2_poses = t2_pose;
                state.turn = turn;
                all_states.push_back(state);
                // If any agent from team1 reaches a winning cell it is a final state
                for(const auto& pose : state.team1_poses)
                {
                    int x = std::get<0>(pose);
                    int y = std::get<1>(pose);
                    for(const auto& cell : this->winning_cells)
                        if(std::make_tuple(x, y) == cell)
                            this->final_states.push_back(state);
                }
            }
        }
    }
    return all_states;
}

Multiagent_State Multiagent_Env::get_transition(Multiagent_State state, std::vector<Action> actions) {
    // If any agent from team1 is in the same cell as an agent from team2 then it is a sink state
    Multiagent_State dest_state = Multiagent_State();
    dest_state.turn = 3 - state.turn; // dest_state turn is 1 or 2, whichever is not the current state.turn

    if(state.turn == 1)
    {
        dest_state.team2_poses = state.team2_poses;
        if(actions.size() != this->num_agents_t1)
            std::cerr << "Number of actions passed does not match number of agents in t1" << std::endl;
        for(int i = 0; i < state.team1_poses.size(); i++)
        {
            int x = std::get<0>(state.team1_poses[i]);
            int y = std::get<1>(state.team1_poses[i]);
            int rot = std::get<2>(state.team1_poses[i]);

            if(actions[i] == left)
                rot = rot == 0 ? 3 : rot - 1;
            else if(actions[i] == right)
                rot = rot == 3 ? 0 : rot + 1;
            else if(actions[i] == forward)
            {
                if(rot == 0) // North
                    y = y == 0 ? y : y-1;
                else if(rot == 1) // East
                    x = x == this->width - 1 ? x : x+1;
                else if(rot == 2) // South
                    y = y == this->height - 1 ? y : y+1;
                else if(rot == 3) // West
                    x = x == 0 ? x : x-1;
                else
                    std::cerr << "invalid rotation value for agent" << std::endl;
            }
            else if(actions[i] == done){} // if the action is done this agent does nothing
            dest_state.team1_poses.push_back(std::make_tuple(x, y ,rot));
        }
    }
    else if(state.turn == 2)
    {
        dest_state.team1_poses = state.team1_poses;
        if(actions.size() != this->num_agents_t2)
            std::cerr << "Number of actions passed does not match number of agents in t2" << std::endl;
        for(int i = 0; i < state.team2_poses.size(); i++)
        {
            int x = std::get<0>(state.team2_poses[i]);
            int y = std::get<1>(state.team2_poses[i]);
            int rot = std::get<2>(state.team2_poses[i]);

            if(actions[i] == left)
                rot = rot == 0 ? 3 : rot - 1;
            else if(actions[i] == right)
                rot = rot == 3 ? 0 : rot + 1;
            else if(actions[i] == forward)
            {
                if(rot == 0) // North
                    y = y == 0 ? y : y-1;
                else if(rot == 1) // East
                    x = x == this->width - 1 ? x : x+1;
                else if(rot == 2) // South
                    y = y == this->height - 1 ? y : y+1;
                else if(rot == 3) // West
                    x = x == 0 ? x : x-1;
                else
                    std::cerr << "invalid rotation value for agent" << std::endl;
            }
            else if(actions[i] == done){} // if the action is done this agent does nothing
            dest_state.team2_poses.push_back(std::make_tuple(x, y ,rot));
        }
    }
    else
    {
        std::cerr << "Invalid team in get_transition" << std::endl;
    }

    return dest_state;
}

Graph Multiagent_Env::generate_game_graph() {
    // Generate action combos
    std::vector<std::vector<Action>> t1_action_combos;
    std::vector<std::vector<Action>> t2_action_combos;
    std::vector<Action> currentCombo;
    this->generateActions(currentCombo, this->num_agents_t1, t1_action_combos);
    this->generateActions(currentCombo, this->num_agents_t2, t2_action_combos);

    auto g = Graph();
    g.setSize(this->states.size());
    int n = 0;
    // For each state add a node
    for(int i = 0; i < this->states.size(); i++)
    {
        g.addNode(n, this->states[i].turn);
        this->state_2_node[this->states[n]] = n;
        n++;
    }
    // For each state and each action add an edge from state to get_transition(state, action)
    for(int i = 0; i < this->states.size(); i++)
    {
        if(this->states[i].turn == 1)
        {
            for (const auto& team_action : t1_action_combos)
            {
                auto dest_state = this->get_transition(this->states[i], team_action);
                // TODO Find more efficient way to get index of dest_state
                for(int j = 0; j < this->states.size(); j++)
                {
                    if(this->states[j] == dest_state)
                        g.addEdge(i, j);
                }
            }
        }
    }
    // Iterate over all possible combinations of action for every player on team "turn"

    return g;
}