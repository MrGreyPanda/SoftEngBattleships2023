#include "game_state.h"

#include "helper_functions.h"

// class GameState {
// public:
//     GameState(std::string id_);

// private:
//     std::string id_;
//     std::vector<Player*> players;
//     Phase phase;
//     std::vector<Ship> ships_;
//     unsigned short turn_player_index;
// };

GameState::GameState()
    : id_(HelperFunctions::create_random_id()),
      phase_(Lobby),
      turn_player_index_(0),
      players_({}) {}

GameState::GameState(std::string id_, std::vector<Player> players)
    : id_(id_), phase_(Lobby), turn_player_index_(0), players_(players) {
    ships_.push_back(Ship(Destroyer));
    ships_.push_back(Ship(Submarine));
    ships_.push_back(Ship(Cruiser));
    ships_.push_back(Ship(Battleship));
    ships_.push_back(Ship(Carrier));
}

GameState::GameState(std::string id_, std::vector<std::string> player_ids)
    : id_(id_), phase_(Lobby), turn_player_index_(0) {
    for (auto player_id : player_ids) {
        players_.push_back(Player(player_id));
    }
    ships_.push_back(Ship(Destroyer));
    ships_.push_back(Ship(Submarine));
    ships_.push_back(Ship(Cruiser));
    ships_.push_back(Ship(Battleship));
    ships_.push_back(Ship(Carrier));
}

GameState::~GameState() {}

std::string GameState::get_id() { return id_; }

void GameState::set_phase(Phase phase) { this->phase_ = phase; }

Phase GameState::get_phase() { return phase_; }

unsigned short GameState::get_turn_player_index() { return turn_player_index_; }

void GameState::change_turn_player_index() {
    turn_player_index_ = (turn_player_index_ + 1) % players_.size();
}

std::vector<Player> GameState::get_players() { return players_; }

std::vector<Ship> GameState::get_ships() { return ships_; }