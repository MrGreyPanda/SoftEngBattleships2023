// Adapted from LAMA example project

#pragma once

#include <string>
#include <shared_mutex>
#include <unordered_map>

#include "../common/player.h"

class PlayerManager {

private:

    inline static std::shared_mutex _rw_lock;
    static std::unordered_map<std::string, Player*> _players_lut;

public:
    static bool try_get_player(const std::string& player_id, Player*& player_ptr);
    static bool add_or_get_player(std::string name, const std::string& player_id, Player*& player_ptr);
    static bool remove_player(const std::string& player_id, Player*& player);
};
