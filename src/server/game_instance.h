// Adapted from LAMA example project

#pragma once

#include <vector>
#include <string>
#include <mutex>

#include "../common/game_state/include/player.h"
#include "../common/game_state/include/game_state.h"

/**
 * @brief Tool to maintain a game session. This includes keeping track of the game state and 
 * ensuring that the game state is kept up to date on the clients by passing the updated information 
 * to the ServerNetworkManager instance.
 */
class GameInstance {

private:
    GameState* game_state;
    inline static std::mutex modification_lock;

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
        if (game_state != nullptr) {
            delete game_state;
        }
        game_state = nullptr;
    }
    /**
     * @brief Returns the id of game_state
     * 
     * @return std::string id
     */
    std::string get_id();

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
    bool has_started();
    /**
     * @brief 
     * 
     * @return true if game has ended
     * @return false else
     */
    bool has_ended();

    // game update functions

    /**
     * @brief Adds player to the game if possible
     * 
     * @param new_player Player to be added
     * @return true if succesful
     * @return false else
     */
    bool add_player(Player* new_player);
    /**
     * @brief Removes player from game if possible
     * 
     * @param player Player to be added
     * @return true if succesful
     * @return false else
     */
    bool remove_player(Player* player);
    /**
     * @brief Attempts to start the game
     * 
     * @return true if succesful
     * @return false else
     */
    bool start_game();
    /**
     * @brief Places shot on the corresponding boards and updates the game_state according to the rules
     * 
     * @return true 
     * @return false 
     */
    bool shoot();
    /**
     * @brief Validate the prepared ships for a player and set them on the board. Update the player as ‘is prepared’.
     * 
     * @return true 
     * @return false 
     */
    bool player_prepared();
};

