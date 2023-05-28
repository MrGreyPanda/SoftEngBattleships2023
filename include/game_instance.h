// Adapted from LAMA example project

#pragma once

#include <mutex>
#include <string>
#include <vector>

#include "game_state.h"
#include "player.h"

/**
 * @brief Tool to maintain a game session. This includes keeping track of the
 * game state and ensuring that the game state is kept up to date on the
 * clients by passing the updated information to the ServerNetworkManager
 * instance.
 */
class GameInstance {
   public:
    /**
     * @brief Construct a new GameInstance object
     *
     */
    GameInstance();
    /**
     * @brief Destroy the GameInstance object
     *
     */
    ~GameInstance() {
        if (game_state_ != nullptr) {
            delete game_state_;
        }
    }
    /**
     * @brief Returns the id of game_state
     *
     * @return std::string id
     */
    std::string get_id() const;

    /**
     * @brief Returns the game_state
     *
     * @return GameState*
     */
    GameState* get_game_state();

    /**
     * @brief
     *
     * @return true if game has started
     * @return false else
     */
    bool has_started() const;
    /**
     * @brief
     *
     * @return true if game has ended
     * @return false else
     */
    bool has_ended() const;

    // game update functions

    /**
     * @brief Adds player to the game if possible
     *
     * @param new_player Player to be added
     * @return true if succesful
     * @return false else
     */
    bool try_add_player(Player* new_player);

    /**
     * @brief Store that the player with the given ID is ready to go from the
     * lobby to the preparation phase.
     *
     * @param player_id
     */
    bool set_player_ready(std::string player_id);

    /**
     * @brief Removes player from game if possible
     *
     * @param player Player to be removed
     * @return true if succesful
     * @return false else
     */
    bool try_remove_player(Player* player);

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool all_players_ready() const;

    /**
     * @brief Attempts to start the game
     *
     * @return true if succesful
     * @return false else
     */
    bool start_preparation();

    /**
     * @brief Attempts to transition from preparation to battle phase
     *
     * @return true
     * @return false
     */
    bool start_battle();

    /**
     * @brief Places shot on the corresponding boards and updates the
     * game_state according to the rules
     *
     * @param player_id
     * @param other_player_id
     * @param x
     * @param y
     * @param is_valid
     * @param has_hit
     * @param has_destroyed_ship
     * @param destroyed_ship
     * @param has_won_game
     */
    void handle_shot(const std::string& player_id,
                     std::string& other_player_id, const unsigned short x,
                     const unsigned short y, bool& is_valid, bool& has_hit,
                     bool& has_destroyed_ship, ShipData& destroyed_ship,
                     bool& has_won_game);
    /**
     * @brief Validate the prepared ships for a player and set them on the
     * board. Update the player as ‘is prepared’.
     *
     * @return true
     * @return false
     */
    bool set_player_prepared(const std::string& player_id,
                             const std::array<ShipData, 5>& ships);

    /**
     * @brief Checks if all players are prepared
     *
     * @return true
     * @return false
     */
    bool all_players_prepared() const;

    /**
     * @brief Checks for a player with the given id
     *
     * @param player_id
     * @return true if found
     * @return false else
     */
    bool has_player(std::string player_id) const;

    /**
     * @brief Gets id of player that wasn't passed as parameter
     *
     * @param player_id
     * @return std::string
     */
    std::string try_get_other_player_id(std::string player_id) const;

    /**
     * @brief Checks if game is full
     *
     * @return true
     * @return false
     */
    bool is_full() const;

   private:
    GameState* game_state_;
    inline static std::mutex lock_;
};
