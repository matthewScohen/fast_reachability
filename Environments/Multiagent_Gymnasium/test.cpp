#include <tuple>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include "Multiagent_Env.h"
#include "../../solver.h"
#include <chrono>

void save_strategy(const std::map<std::string, std::string>& strategy, const std::string& filepath)
{
    std::ofstream outputFile(filepath);
    if (outputFile.is_open())
    {
        for (const auto& pair : strategy)
            outputFile << pair.first << "," << pair.second << std::endl;
        outputFile.close();
        std::cout << "Strategy has been written to " << filepath << std::endl;
    }
    else
        std::cerr << "Unable to open file" << std::endl;
}

int main()
{
    int width = 20;
    int height = 20;
    int num_agents_t1 = 1;
    int num_agents_t2 = 1;

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::tuple<int, int>> winning_cells;
    winning_cells.emplace_back(5, 5);
    auto env = Multiagent_Env(width, height, num_agents_t1, num_agents_t2, winning_cells);
    auto graph_done = std::chrono::high_resolution_clock::now();

    auto attractor_strategy_p1 = attr(env.game_graph, env.game_graph.getFinalStates());
    auto P1_done = std::chrono::high_resolution_clock::now();
    std::cout << "P1 strategy computed" << std::endl;
    auto attractor_strategy_p2 = attr(env.game_graph, env.p2_final_state_indexes, 2);
    auto P2_done = std::chrono::high_resolution_clock::now();
    std::cout << "P2 strategy computed" << std::endl;
    std::map<std::string, std::string> p1_strategy = std::get<1>(attractor_strategy_p1);
    std::map<std::string, std::string> p2_strategy = std::get<1>(attractor_strategy_p2);

    std::string file_path1 = std::to_string(width) + "X" + std::to_string(height) + "_" + std::to_string(num_agents_t1) +
            "_" + std::to_string(num_agents_t2) + "_" + "P1.strategy";

    std::string file_path2 = std::to_string(width) + "X" + std::to_string(height) + "_" + std::to_string(num_agents_t1) +
                             "_" + std::to_string(num_agents_t2) + "_" + "P2.strategy";
    save_strategy(p1_strategy, file_path1);
    save_strategy(p2_strategy, file_path2);

    auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(P2_done - start).count();
    auto graph_time = std::chrono::duration_cast<std::chrono::milliseconds>(graph_done - start).count();
    auto p1_time = std::chrono::duration_cast<std::chrono::milliseconds>(P1_done - graph_done).count();
    auto p2_time = std::chrono::duration_cast<std::chrono::milliseconds>(P2_done - P1_done).count();
    std::cout << "Graph Size: " << env.game_graph.getSize() << std::endl;
    std::cout << "Total time: " << total_time << "ms" << std::endl;
    std::cout << "Time to generate graph: " << graph_time << "ms" << std::endl;
    std::cout << "Time to generate P1 strategy " << p1_time << "ms" << std::endl;
    std::cout << "Time to generate P2 strategy " << p2_time << "ms" << std::endl;

    return 0;
}