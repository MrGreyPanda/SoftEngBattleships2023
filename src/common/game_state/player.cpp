#include "player.h"

Player::Player(const std::string &id)
    : id_(id),
      is_ready_(false),
      is_prepared_(false),
      own_board_(OwnBoard()),
      enemy_board_(EnemyBoard()) {}

std::string Player::get_id() const { return id_; }

void Player::set_id(std::string id) { this->id_ = id; }

void Player::set_ready() { is_ready_ = true; }

void Player::unset_ready() { is_ready_ = false; }

void Player::set_prepared() { is_prepared_ = true; }

void Player::unset_prepared() { is_prepared_ = false; }

bool Player::get_is_ready() const { return is_ready_; }

bool Player::get_is_prepared() const { return is_prepared_; }

OwnBoard &Player::get_own_board() { return own_board_; }

EnemyBoard &Player::get_enemy_board() { return enemy_board_; }

bool Player::is_valid_shot(const unsigned short &x, const unsigned short &y) {
    return this->get_enemy_board().is_valid_shot(x, y);
}

bool Player::has_lost() const { return own_board_.all_ships_sunk(); }

Player::~Player() {}
