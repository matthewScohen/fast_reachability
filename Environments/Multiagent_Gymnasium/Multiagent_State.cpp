#include <string>
#include "Multiagent_State.h"

Multiagent_State::Multiagent_State(std::vector<std::tuple<int, int, int>> team1_poses, std::vector<std::tuple<int, int, int>> team2_poses, int turn) {
    this->team1_poses = team1_poses;
    this->team2_poses = team2_poses;
    this->turn = turn;
}

Multiagent_State::Multiagent_State() {
    this->team1_poses = std::vector<std::tuple<int, int, int>>();
    this->team2_poses = std::vector<std::tuple<int, int, int>>();
    this->turn = -1;
}

bool Multiagent_State::operator==(const Multiagent_State &other) const {
    return this->turn == other.turn && this->team1_poses == other.team1_poses && this->team2_poses == other.team2_poses;
}

bool Multiagent_State::operator<(const Multiagent_State &other) const {
    if(this->turn < other.turn)
        return true;
    if (this->team1_poses != other.team1_poses)
        return std::lexicographical_compare(this->team1_poses.begin(), this->team1_poses.end(),
                                            other.team1_poses.begin(), other.team1_poses.end());
    return std::lexicographical_compare(this->team2_poses.begin(), this->team2_poses.end(),
                                        other.team2_poses.begin(), other.team2_poses.end());
}

std::string Multiagent_State::get_string_representation() {
    std::string string_key = std::to_string(this->turn);
    string_key += "_";
    for(auto & team1_pose : this->team1_poses)
    {
        string_key += std::to_string(std::get<0>(team1_pose));
        string_key += std::to_string(std::get<1>(team1_pose));
        string_key += std::to_string(std::get<2>(team1_pose));
    }
    string_key += "_";
    for(auto & team2_pose : this->team2_poses)
    {
        string_key += std::to_string(std::get<0>(team2_pose));
        string_key += std::to_string(std::get<1>(team2_pose));
        string_key += std::to_string(std::get<2>(team2_pose));
    }
    return string_key;
}
