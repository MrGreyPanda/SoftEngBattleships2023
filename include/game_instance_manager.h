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
    /**
     * @brief Destroys the GameInstanceManager object.
     */
    ~GameInstanceManager();

    /**
     * @brief Tries to return a GameInstance given the game_id.
     *
     * @param game_id
     * @param game_instance_ptr
     * @return Pointer to GameInstance if found, nullptr if not found.
     */
    static GameInstance* get_game_instance(const std::string& game_id);

    /**
     * @brief Tries to add the player to any open GameInstance.
     *
     * @param player
     * @param game_instance_ptr
     * @return Pointer to GameInstance where Player was added, nullptr if no
     * game was available.
     */
    static GameInstance* add_player_to_any_game(Player* player_ptr);

    /**
     * @brief Tries to add player to a specific GameInstance.
     *
     * @param player
     * @param game_instance_ptr
     * @return True if succesful, false otherwise.
     */
    static bool try_add_player(Player* player_ptr,
                               GameInstance*& game_instance_ptr);

    /**
     * @brief Removes a certain player from a GameInstance
     *
     * @param player
     * @param game_id
     * @return True if sucessful, false otherwise.
     */
    static bool try_remove_player(Player* player_ptr,
                                  GameInstance*& game_instance_ptr);

    /**
     * @brief Deletes a GameInstance
     * 
     * @param game_id 
     * @return true if successful, false otherwise
     */
    static bool delete_game_(const std::string& game_id);

   private:
    /**
     * @brief Creates a new GameInstance and adds it to games_.
     *
     * @return Pointer to added GameInstance.
     */
    static GameInstance* create_new_game_();

    /**
     * @brief Finds the GameInstance with player_id in it.
     *
     * @param player_id
     * @return GameInstance*, nullptr if no such GameInstance exists.
     */
    static GameInstance* find_game_by_player_id_(const std::string& player_id);

    /**
     * @brief Finds a game with less than 2 players
     *
     * @return GameInstance*, nullptr if no suitable game exists.
     */
    static GameInstance* find_joinable_game_instance_();

    inline static std::shared_mutex games_lock_;
    static std::unordered_map<std::string, GameInstance*> games_;

    // Allows the tests to access private member functions and variables.
    FRIEND_TEST(GameInstanceManagerTest, TryAddPlayer);
    FRIEND_TEST(GameInstanceManagerTest, FindGameByPlayerId);
    FRIEND_TEST(GameInstanceManagerTest, AddPlayerToAnyGame);
    FRIEND_TEST(GameInstanceManagerTest, TryRemovePlayer);
    FRIEND_TEST(GameInstanceManagerTest, FindJoinableGameInstance);
};
