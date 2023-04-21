#pragma once
#include <string>
#include "board.h"
/*
The class attributes are:
id: string, unique player ID
is_ready: bool, TRUE if the player in the lobby is ready to play
is_prepared: bool, TRUE if the player has placed all the ships and confirmed, via button press, that he is ready, FALSE otherwise
own_board: OwnBoard, a board representing the board the user places his ships and shots from the opponent are displayed.
enemy_board: EnemyBoard, a board representing the board which the user uses to place shots at the enemy and the opponents ships are revealed, turn by turn.
placed_ships: std::vector<std::pair<Ship, bool>>, holds all ships to be placed
The class operations are:
place_ship: player places ship on board, returns TRUE if the placement was successful
shoot: bool, player selects a cell on the opponent’s grid, returns FALSE if it was a miss and TRUE if it was a hit, the function can only be called if the cell hasn’t been shot at already
*/


class Player {
public:
    Player(unsigned short board_size);
    Player(unsigned short board_size, unsigned short n_ships);
    Player(std::string id);

    bool place_ship(const std::pair<unsigned short, unsigned short> &coords[]);
    bool shoot(const std::pair<unsigned short, unsigned short> &coord);

private:
    std::string id;
    bool is_ready;
    bool is_prepared;
    OwnBoard own_board;
    EnemyBoard enemy_board;
};
