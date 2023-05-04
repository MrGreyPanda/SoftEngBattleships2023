// Adapted from LAMA example project

#pragma once

#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <iostream>

#include "player.h"

/**
 * @brief Handles player management in the server. Doesn't exist on the client
 * side!
 */
class PlayerManager {
   private:
    inline static std::shared_mutex rw_lock_;
    static std::unordered_map<std::string, Player*> players_;

   public:
    /**
     * @brief Retrieves a player form the player list.
     *
     * @param player_id
     * 
     * @return pointer to player with player_id, nullptr if not found
     */
    static Player *try_get_player(const std::string& player_id);
    /**
     * @brief Adds new player to the player list or retrieves the existing
     * player if present.
     *
     * @param player_id
     *
     * @return pointer to found/added player
     */
    static Player *add_or_get_player(const std::string& player_id);
    /**
     * @brief Removes the player form the player list.
     *
     * @param player_id
     * 
     * @return true if succesful, false otherwise
     */
    static bool remove_player(const std::string& player_id);

    ~PlayerManager();
};
