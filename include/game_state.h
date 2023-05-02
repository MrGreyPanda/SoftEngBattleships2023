#pragma once
#include <string>
#include <utility>
#include <vector>

#include "player.h"
/*
The class attributes are
id: string, unique game ID
players: vector<player*>, representing the players playing the current game
phase: int, number representing which phase the game is in (0) lobby (not
started yet), (1) preparation phase, (2) battle phase, (3) game ended. ships_:
vector, the ships_ agreed upon for this game turn_player_index: unsigned short,
the index of the player in the players array whose turn it is.
*/

// Enum describing the different phases of the game
enum Phase { Lobby = 0, Preparation = 1, Battle = 2, End = 3 };

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
     * @param id The id of the game
     * @param players The players in the game
     */
    GameState(std::string id, std::vector<Player> players);

    /**
     * @brief Construct a new Game State object
     * @param id The id of the game
     * @param player_ids The ids of the players in the game
     */
    GameState(std::string id, std::vector<std::string> player_ids);

    /**
     * @brief Destroy the Game State object
     */
    ~GameState();

    /**
     * @brief Get the id of the game
     * @return The id of the game
     */
    std::string get_id();

    /**
     * @brief set the phase of the game
     */
    void set_phase(Phase phase);

    /**
     * @brief Get the phase of the game
     * @return The phase of the game
     */
    Phase get_phase();

    /**
     * @brief get turn player index
     */
    unsigned short get_turn_player_index();

    /**
     * @brief change turn player index
     */
    void change_turn_player_index();

   private:
    std::string id;
    std::vector<Player> players;
    Phase phase;
    std::vector<Ship> ships_;
    unsigned short turn_player_index;
};
