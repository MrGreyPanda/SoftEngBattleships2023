#pragma once
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "player.h"

// Enum describing the different phases of the game
enum Phase { Connection = 0, Lobby = 1, Preparation = 2, Battle = 3, End = 4 };

class GameState {
   public:
    /**
     * @brief Construct a new Game State object
     * This constructor is used to create an empty game state, representing
     * a game with no players that didn't start yet.
     */
    GameState();

    /**
     * @brief Construct a new Game State object
     * @param id_ The id_ of the game
     * @param players The players in the game
     */
    GameState(std::string id, std::vector<Player*> players);

    /**
     * @brief Destroy the Game State object
     */
    ~GameState();

    /**
     * @brief Get the id_ of the game
     * @return The id_ of the game
     */
    std::string get_id() const;

    /**
     * @brief set the phase of the game
     */
    void set_phase(Phase phase);

    /**
     * @brief Get the phase of the game
     * @return The phase of the game
     */
    Phase get_phase() const;

    /**
     * @brief Get players of the game
     * @return The players of the game
     */
    std::vector<Player*> get_players();

    /**
     * @brief Get player by id_
     * @param id_ The id_ of the player
     * @return The player with the given id_
     */
    Player* get_player_by_id(std::string id_);

    /**
     * @brief Get player by index
     * @param index The index of the player
     * @return The player_id with the given index
     */
    std::string get_player_id_by_index(unsigned short index);

    /**
     * @brief Adds player to the game
     *
     * @return true
     * @return false
     */
    bool add_player(Player*);

    /**
     * @brief Removes player from the game
     *
     * @return true
     * @return false
     */
    bool remove_player(Player*);

    /**
     * @brief Checks if game is full
     *
     * @return true
     * @return false
     */
    bool is_full() const;

    /**
     * @brief Set the player with the given ID as ready to go from the lobby
     * phase to the preparation phase.
     *
     * @param player_id
     */
    bool set_player_ready(std::string player_id);

    /**
     * @brief get turn player index
     */
    unsigned short get_turn_player_index() const;

    /**
     * @brief get turn player id
     */
    std::string get_turn_player_id() const;

    /**
     * @brief change turn player index
     */
    void change_turn_player_index();

    /**
     * @brief Set the player to prepared to go from the lobby to the preparation
    */
    bool start_preparation();

    /**
     * @brief Set the player to prepared to go from the preparation to the battle
    */
    bool start_battle();

    /**
     * @brief Get the other player id
     * @param id The id of the player
     */
    std::string get_other_player_id(std::string id) const;

    /**
     * @brief Set the game id
     * @param game_id The id of the game
     */
    void set_game_id(const std::string& game_id);
    /**
     * @brief Returns whether all players are ready to go from the lobby phase
     * to the preparation phase.
     *
     * @return 'true' if all players in the game are ready,
     * @return 'false' else
     */
    bool all_players_ready() const;

    /**
     * @brief Returns whether all players are ready to go from the preparation
     * phase to the battle phase.
     *
     * @return 'true' if all players in the game are ready,
     * @return 'false' else
     */
    bool all_players_prepared() const;

    /**
     * @brief Reset all players' states to 'not ready' and set the game phase to 'lobby'.
     */
    void reset_state();

   private:
    std::string id_;
    std::vector<Player*> players_;
    Phase phase_;
    unsigned short turn_player_index_;
};
