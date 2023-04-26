#include "player.h"

Player::Player(unsigned short board_size, std::string id) : id(id) own_board(OwnBoard(board_size, 5)), enemy_board(EnemyBoard(board_size, 5)), is_prepared(false), is_ready(false){}

Player::Player(unsigned short board_size, unsigned short n_ships, std::string id) : id(id), own_board(OwnBoard(board_size, n_ships)), enemy_board(EnemyBoard(board_size, n_ships)), is_prepared(false), is_ready(false) {}

Player::Player(std::string id) : id(id), is_ready(false), is_prepared(false), own_board(OwnBoard(10, 5)), enemy_board(EnemyBoard(10, 5)) {}

bool Player::place_ship(const std::pair<unsigned short, unsigned short> &coords[][], ShipCategory shiptype){
    
    return own_board.place_ship(coords, shiptype);
}

bool Player::shoot(const std::pair<unsigned short, unsigned short> &coord){
    if(enemy_board.is_valid_shot(coord)){
        // Send shot to server
        // return true if hit
        // return false if miss
    }
}