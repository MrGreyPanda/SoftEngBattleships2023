#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "board.h"

/**
 * @brief The player class
 */
class Player {
   public:
    // /**
    //  * @brief Creates a player with a given board size and defautl ships
    //  * @param board_size The size of the board
    //  * @param id The id of the player
    // */
    // Player(unsigned short board_size, std::string id);

    // /**
    //  * @brief Creates a player with a given board size and number of ships
    //  * @param board_size The size of the board
    //  * @param n_ships The number of ships
    //  * @param id The id of the player
    // */
    // Player(unsigned short board_size, unsigned short n_ships, std::string
    // id);

    /**
     * @brief Creates a player with a default board size and number of ships
     * @param id The id of the player
     */
    Player(const std::string &id);

    ~Player();

    /**
     * @brief Returns the id of the player
     */
    std::string get_id() const;

    /**
     * @brief Sets the players id
     */
    void set_id(std::string id);

    /**
     * @brief sets the player as ready
     */
    void set_ready();

    /**
     * @brief sets the player as not ready
     */
    void unset_ready();

    /**
     * @brief sets the player as prepared
     */
    void set_prepared();

    /**
     * @brief sets the player as not prepared
     */
    void unset_prepared();

    /**
     * @brief Returns the player' state of readiness
     * @return True if the player is ready, false otherwise
     */
    bool get_is_ready() const;

    /**
     * @brief Returns the player' state of preparedness
     * @return True if the player is prepared, false otherwise
     */
    bool get_is_prepared() const;

    /**
     * @brief Checks if a given placement is valid, if it is, places the ship
     * @param coords The coordinates of the ship to be placed
     */

    /**
     * @brief Returns the player's own board
     */
    OwnBoard &get_own_board();

    /**
     * @brief Returns the player's enemy board
     */
    EnemyBoard &get_enemy_board();

    /**
     * @brief Try to shoot at a given coordinate
     * @param x The x coordinate
     * @param y The y coordinate
     * TODO: Send shooting Request to Server and wait for response
     */
    bool shoot(const short &x, const short &y);

    /**
     * @brief Check if this player has lost
     */
    bool has_lost() const;

    bool is_own_turn;

    bool has_shot = false;

   private:
    std::string id_;
    bool is_ready_;
    bool is_prepared_;
    OwnBoard own_board_;
    EnemyBoard enemy_board_;
};
