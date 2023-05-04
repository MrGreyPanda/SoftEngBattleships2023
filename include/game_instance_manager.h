// Adapted from LAMA example project

#pragma once

#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "game_instance.h"
#include "gtest/gtest.h"

/**
 * @brief Manages game instances. Makes hosting multiple game instances
 * possible.
 *
 */
class GameInstanceManager {
   public:
    ~GameInstanceManager();

    /**
     * @brief Tries to return a game instance given the game ID
     *
     * @param game_id
     * @param game_instance_ptr
     * @return true if succesful
     * @return false else
     */
    static GameInstance* get_game_instance(const std::string& game_id);

    /**
     * @brief Tries to add the player to a game, preferably a game where a
     * player is already waiting
     *
     * @param player
     * @param game_instance_ptr
     * @return true if succesful
     * @return false else
     */
    static GameInstance* add_player_to_any_game(Player* player_ptr);

    /**
     * @brief Tries to return a game instance given the game ID
     *
     * @param player
     * @param game_instance_ptr
     * @return true if succesful
     * @return false else
     */
    static bool try_add_player(Player* player_ptr, GameInstance *&game_instance_ptr);

    /**
     * @brief Removes a certain player from a game instance
     *
     * @param player
     * @param game_id
     * @return true if sucessful
     * @return false else
     */
    static bool try_remove_player(Player* player_ptr, GameInstance *&game_instance_ptr);

   private:
    /**
     * @brief Creates a new game
     *
     * @return GameInstance*
     */
    static GameInstance* create_new_game_();

    /**
     * @brief Finds the game with player_id in it
     *
     * @param player_id
     * @return GameInstance*, nullptr if no game exists
     */
    static GameInstance* find_game_by_player_id_(const std::string& player_id);

    /**
     * @brief Finds a game with less than 2 players
     *
     * @return GameInstance*, nullptr if no suitable game exists
     */
    static GameInstance* find_joinable_game_instance_();

    inline static std::shared_mutex games_lock_;
    static std::unordered_map<std::string, GameInstance*> games_;

    FRIEND_TEST(GameInstanceManagerTest, TryAddPlayer);
    FRIEND_TEST(GameInstanceManagerTest, FindGameByPlayerId);
    FRIEND_TEST(GameInstanceManagerTest, AddPlayerToAnyGame);
    FRIEND_TEST(GameInstanceManagerTest, TryRemovePlayer);
    FRIEND_TEST(GameInstanceManagerTest, FindJoinableGameInstance);
};
