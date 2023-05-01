#include "player.h"

// Player::Player(unsigned short board_size, std::string id) : id(id)
// own_board(OwnBoard(board_size, 5)), enemy_board(EnemyBoard(board_size, 5)),
// is_prepared(false), is_ready(false){}

// Player::Player(unsigned short board_size, unsigned short n_ships,
// std::string id) : id(id), own_board(OwnBoard()),
// enemy_board(EnemyBoard(board_size, n_ships)), is_prepared(false),
// is_ready(false) {}

Player::Player(std::string id)
    : id(id),
      is_ready(false),
      is_prepared(false),
      own_board(OwnBoard()),
      enemy_board(EnemyBoard()) {}

std::string Player::get_id() { return id; }

void Player::set_id(std::string id) { this->id = id; }

void Player::set_ready() { is_ready = true; }

void Player::unset_ready() { is_ready = false; }

void Player::set_prepared() { is_prepared = true; }

void Player::unset_prepared() { is_prepared = false; }

bool Player::is_player_ready() { return is_ready; }

bool Player::is_player_prepared() { return is_prepared; }

bool Player::place_ship(
    const std::vector<std::pair<unsigned short, unsigned short>> coords,
    ShipCategory shiptype) {
    return own_board.place_ship(coords, shiptype);
}

bool Player::shoot(const std::pair<unsigned short, unsigned short> &coord) {
    if (enemy_board.is_valid_shot(coord)) {
        // Send shot to server
        // return true if hit
        // return false if miss
    }
}

Player::~Player() {}