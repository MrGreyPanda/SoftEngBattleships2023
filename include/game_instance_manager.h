// Adapted from LAMA example project

#pragma once

#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "game_instance.h"

/**
 * @brief Manages game instances. Makes hosting multiple game instances possible.
 * 
 */
class GameInstanceManager {
   public:
    /**
     * @brief Tries to return a game instance given the game ID
     * 
     * @param game_id 
     * @param game_instance_ptr 
     * @return true if succesful
     * @return false else
     */
    static bool get_game_instance(const std::string& game_id,
                                  GameInstance*& game_instance_ptr);

    /**
     * @brief Tries to add the player to a game, preferably a game where a player is already waiting
     * 
     * @param player 
     * @param game_instance_ptr 
     * @return true if succesful
     * @return false else
     */
    static bool add_player_to_any_game(Player* player,
                                       GameInstance*& game_instance_ptr);

    /**
     * @brief Tries to return a game instance given the game ID
     * 
     * @param player 
     * @param game_instance_ptr 
     * @return true if succesful
     * @return false else
     */
    static bool try_add_player(Player* player,
                               GameInstance*& game_instance_ptr);

    /**
     * @brief Removes a certain player from a game instance
     * 
     * @param player 
     * @param game_id 
     * @return true if sucessful
     * @return false else
     */
    static bool try_remove_player(Player* player, const std::string& game_id);
    static bool try_remove_player(Player* player,
                                  GameInstance*& game_instance_ptr);

   private:
   /**
    * @brief Creates a new game
    * 
    * @return GameInstance* 
    */
    static GameInstance* create_new_game();

    /**
     * @brief Finds the game with player_id in it
     * 
     * @param player_id 
     * @return GameInstance*, nullptr if no game exists
     */
    static GameInstance* _find_game_by_player_id(const std::string& player_id);

    /**
     * @brief Finds a game with less than 2 players
     * 
     * @return GameInstance*, nullptr if no suitable game exists
     */
    static GameInstance* _find_joinable_game_instance();
    
    inline static std::shared_mutex games_lut_lock;
    static std::unordered_map<std::string, GameInstance*> games_lut;
};
