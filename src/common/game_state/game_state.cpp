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

GameState::GameState(std::string id, std::vector<Player*> players)
    : id_(id), phase_(Lobby), turn_player_index_(0), players_(players) {
    ships_.push_back(Ship(Destroyer));
    ships_.push_back(Ship(Submarine));
    ships_.push_back(Ship(Cruiser));
    ships_.push_back(Ship(Battleship));
    ships_.push_back(Ship(Carrier));
}

// Not sure if this is needed, will confirm eventually
// GameState::GameState(std::string id, std::vector<std::string> player_ids)
//     : id(id), phase(Lobby), turn_player_index(0) {
//     for (auto player_id : player_ids) {
//         Player* player = new Player(player_id);
//         players.push_back(player);
//     }
//     ships.push_back(Ship(Destroyer));
//     ships.push_back(Ship(Submarine));
//     ships.push_back(Ship(Cruiser));
//     ships.push_back(Ship(Battleship));
//     ships.push_back(Ship(Carrier));
// }

GameState::~GameState() {}

std::string GameState::get_id() { return id_; }

void GameState::set_phase(Phase phase) { this->phase_ = phase; }

Phase GameState::get_phase() { return phase_; }

std::vector<Player*> GameState::get_players() {return players_;}

bool GameState::add_player(Player* player) {
    if(!is_full()) {
        players_.push_back(player);
        return true;
    }
    return false;
}

bool GameState::remove_player(Player* player) {
    for(auto it = players_.begin(); it != players_.end(); it++){
        if(*it == player){
            players_.erase(it);
            return true;
        }
    }
    return false;
}

bool GameState::is_full() {
    if(players_.size() >= 2) {
        return true;
    }
    return false;
}

unsigned short GameState::get_turn_player_index() { return turn_player_index_; }

void GameState::change_turn_player_index() {
    turn_player_index_ = (turn_player_index_ + 1) % players_.size();
}

std::vector<Ship> GameState::get_ships() { return ships_; }