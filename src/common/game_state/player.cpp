#include "player.h"

// Player::Player(unsigned short board_size, std::string id) : id(id)
// own_board(OwnBoard(board_size, 5)), enemy_board(EnemyBoard(board_size, 5)),
// is_prepared(false), is_ready(false){}

// Player::Player(unsigned short board_size, unsigned short n_ships,
// std::string id) : id(id), own_board(OwnBoard()),
// enemy_board(EnemyBoard(board_size, n_ships)), is_prepared(false),
// is_ready(false) {}

Player::Player(const std::string &id)
    : id_(id),
      is_ready_(false),
      is_prepared_(false),
      own_board_(OwnBoard()),
      enemy_board_(EnemyBoard()){}

std::string Player::get_id() { return id_; }

void Player::set_id(std::string id) { this->id_ = id; }

void Player::set_ready() { is_ready_ = true; }

void Player::unset_ready() { is_ready_ = false; }

void Player::set_prepared() { is_prepared_ = true; }

void Player::unset_prepared() { is_prepared_ = false; }

bool Player::get_is_ready() { return is_ready_; }

bool Player::get_is_prepared() { return is_prepared_; }

OwnBoard Player::get_own_board() { return own_board_; }

EnemyBoard Player::get_enemy_board() { return enemy_board_; }

bool Player::shoot(const short &x, const short &y) {
    if (this->get_enemy_board().is_valid_shot(x, y)) {
        // Send shot to server
        // return true if hit
        // return false if miss
    }
    return false;
}

bool Player::has_lost() { return own_board_.all_ships_sunk(); }

Player::~Player() {
    own_board_.~OwnBoard();
    enemy_board_.~EnemyBoard();
}