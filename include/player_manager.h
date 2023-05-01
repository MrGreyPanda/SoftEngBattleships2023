// Adapted from LAMA example project

#pragma once

#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "player.h"

/**
 * @brief Handles player management during a game instance.
 */
class PlayerManager {
   private:
    inline static std::shared_mutex rw_lock;
    static std::unordered_map<std::string, Player*> players;

   public:
    /**
     * @brief Retrieves a player form the player list.
     *
     * @param player_id
     * @param player_ptr
     */
    static bool try_get_player(const std::string& player_id,
                               Player*& player_ptr);
    /**
     * @brief Adds new player to the player list or retrieves the existing
     * player if present.
     *
     * @param player_id
     * @param player_ptr
     */
    static bool add_or_get_player(const std::string& player_id,
                                  Player*& player_ptr);
    /**
     * @brief Removes the player form the player list.
     *
     * @param player_id
     * @param player
     */
    static bool remove_player(const std::string& player_id, Player*& player);
};
