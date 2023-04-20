#include "player.h"

Player::Player() : own_board(OwnBoard(10, 5));

Player(unsigned short board_size) : own_board(OwnBoard(board_size, 5)), enemy_board(EnemyBoard(board_size, 5)){}

Player(unsigned short board_size, unsigned short n_ships) : own_board(OwnBoard(board_size, n_ships)), enemy_board(EnemyBoard(board_size, n_ships)) {}

bool Player::place_ship(const std::pair<unsigned short, unsigned short> &coords[][], ShipCategory shiptype){
    
    return own_board.place_ship(coords, shiptype);
}

bool shoot(const std::pair<unsigned short, unsigned short> &coord);