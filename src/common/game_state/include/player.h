#pragma once
#include <string>
#include <utility>
#include <vector>
#include "board.h"
/*
The class attributes are:
id: string, unique player ID
is_ready: bool, TRUE if the player in the lobby is ready to play
is_prepared: bool, TRUE if the player has placed all the ships and confirmed, via button press, that he is ready, FALSE otherwise
own_board: OwnBoard, a board representing the board the user places his ships and is_shot from the opponent are displayed.
enemy_board: EnemyBoard, a board representing the board which the user uses to place is_shot at the enemy and the opponents ships are revealed, turn by turn.
placed_ships: std::vector<std::pair<Ship, bool>>, holds all ships to be placed
The class operations are:
place_ship: player places ship on board, returns TRUE if the placement was successful
shoot: bool, player selects a cell on the opponent’s grid, returns FALSE if it was a miss and TRUE if it was a hit, the function can only be called if the cell hasn’t been shot at already
*/


class Player {
public:

    /**
     * @brief Creates a player with a given board size and defautl ships
     * @param board_size The size of the board
     * @param id The id of the player
    */
    Player(unsigned short board_size, std::string id);

    /**
     * @brief Creates a player with a given board size and number of ships
     * @param board_size The size of the board
     * @param n_ships The number of ships
     * @param id The id of the player
    */
    Player(unsigned short board_size, unsigned short n_ships, std::string id);

    /**
     * @brief Creates a player with a default board size and number of ships
     * @param id The id of the player
    */
    Player(std::string id);

    ~Player();

    /**
     * @brief Returns the id of the player
    */
    std::string get_id();
    
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
    bool is_player_ready();

    /**
     * @brief Returns the player' state of preparedness
     * @return True if the player is prepared, false otherwise
    */
    bool is_player_prepared();

    /**
     * @brief Checks if a given placement is valid, if it is, places the ship
     * @param coords The coordinates of the ship to be placed
    */
    bool place_ship(const std::pair<unsigned short, unsigned short> coords[]);

    /**
     * @brief Try to shoot at a given coordinate
     * @param coord The coordinates of the shot to be placed
     * TODO: Send shooting Request to Server and wait for response
    */
    bool shoot(const std::pair<unsigned short, unsigned short> &coord);

private:
    std::string id;
    bool is_ready;
    bool is_prepared;
    OwnBoard own_board;
    EnemyBoard enemy_board;
};
