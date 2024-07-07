#include <tuple>
#include <vector>
#include <functional>
#include <iostream>
#include "Multiagent_Env.h"

int main()
{
    std::vector<std::tuple<int, int>> winning_cells;
    winning_cells.emplace_back(1, 1);
    auto env = Multiagent_Env(2, 2, 1, 1, winning_cells);
    auto t1_p = std::vector<std::tuple<int, int, int>>();
    auto t2_p = std::vector<std::tuple<int, int, int>>();
    t1_p.emplace_back(0, 0, 0);
    t2_p.emplace_back(2, 3, 3);

    auto s = Multiagent_State(t1_p, t2_p, 2);
    auto actions = std::vector<Action>();
    actions.push_back(forward);

    Multiagent_State dest_state = env.get_transition(s, actions);
    std::cout << "done" << std::endl;
    return 0;
}