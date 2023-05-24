#include "game_state.h"

#include "helper_functions.h"

GameState::GameState()
    : id_(HelperFunctions::create_random_id()),
      phase_(Connection),
      turn_player_index_(0),
      players_({}) {}

GameState::GameState(std::string id, std::vector<Player*> players)
    : id_(id), phase_(Connection), turn_player_index_(0), players_(players) {}

GameState::~GameState() {}

std::string GameState::get_id() const { return id_; }

void GameState::set_phase(Phase phase) { this->phase_ = phase; }

Phase GameState::get_phase() const { return phase_; }

std::vector<Player*> GameState::get_players() { return players_; }

Player* GameState::get_player_by_id(std::string id_) {
    for (Player* player_ptr : players_) {
        if (player_ptr->get_id() == id_) {
            return player_ptr;
        }
    }
    return nullptr;
}

std::string GameState::get_player_id_by_index(unsigned short index) {
    if (index < players_.size()) {
        return players_[index]->get_id();
    }
    return "";
}

bool GameState::add_player(Player* player) {
    if (!is_full()) {
        players_.push_back(player);
        return true;
    }
    return false;
}

bool GameState::remove_player(Player* player) {
    if (players_.size() == 0) {
        return false;
    }
    for (auto it = players_.begin(); it != players_.end(); it++) {
        if (*it == player) {
            players_.erase(it);
            return true;
        }
    }
    return false;
}

bool GameState::is_full() const { return players_.size() >= 2; }

bool GameState::set_player_ready(std::string player_id) {
    Player* player = get_player_by_id(player_id);
    if (player == nullptr) {
        return false;
    }
    player->set_ready();
    return true;
}

unsigned short GameState::get_turn_player_index() const {
    return turn_player_index_;
}

std::string GameState::get_turn_player_id() const {
    return players_[turn_player_index_]->get_id();
}

void GameState::change_turn_player_index() {
    turn_player_index_ = (turn_player_index_ + 1) % players_.size();
}

bool GameState::start_preparation() {
    if (players_.size() == 2 && all_players_ready()) {
        phase_ = Phase::Preparation;
        return true;
    }
    return false;
}

bool GameState::start_battle() {
    if (players_.size() == 2 && all_players_prepared()) {
        phase_ = Phase::Battle;
        return true;
    }
    return false;
}

std::string GameState::get_other_player_id(std::string id) const {
    for (unsigned i = 0; i < players_.size(); i++) {
        if (players_.at(i)->get_id() == id) {
            return players_.at((i + 1) % 2)->get_id();
        }
    }

    return "";
}

void GameState::set_game_id(const std::string& game_id) { id_ = game_id; }
bool GameState::all_players_ready() const {
    for (Player* player : players_) {
        if (!player->get_is_ready()) {
            return false;
        }
    }
    return true;
}

bool GameState::all_players_prepared() const {
    for (Player* player : players_) {
        if (!player->get_is_prepared()) {
            return false;
        }
    }
    return true;
}

void GameState::reset_state() {
    for (Player* player : players_) {
    //     // player->set_ready();
    //     // player->set_prepared();
        if(player != nullptr){
            player->get_own_board().reset();
            player->get_enemy_board().reset();
        }
    }
    players_.clear();
    // phase_ = Phase::Connection;
    
}