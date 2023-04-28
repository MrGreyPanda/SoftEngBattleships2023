// Adapted from LAMA example project

#pragma once

#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "game_instance.h"

class GameInstanceManager {
   public:
    // returns true if the desired GameInstance 'game_id' was found or false
    // otherwise. The found game instance is written into game_instance_ptr.
    static bool get_game_instance(const std::string& game_id,
                                  GameInstance*& game_instance_ptr);

    // Try to add 'player' to any game. Returns true if 'player' is
    // successfully added to a GameInstance. The joined GameInstance will be
    // written into 'game_instance_ptr'.
    static bool add_player_to_any_game(Player* player,
                                       GameInstance*& game_instance_ptr);

    // Try to add 'player' to the provided 'game_instance_ptr'. Returns true if
    // success and false otherwise.
    static bool try_add_player(Player* player,
                               GameInstance*& game_instance_ptr);

    static bool try_remove_player(Player* player, const std::string& game_id);
    static bool try_remove_player(Player* player,
                                  GameInstance*& game_instance_ptr);

   private:
    static GameInstance* create_new_game();

    static GameInstance* _find_game_by_player_id(const std::string& player_id);

    static GameInstance* _find_joinable_game_instance();

    inline static std::shared_mutex games_lut_lock;
    static std::unordered_map<std::string, GameInstance*> games_lut;
};
