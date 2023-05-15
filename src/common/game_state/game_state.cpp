#include "game_state.h"

#include "helper_functions.h"

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

GameState::~GameState() {}

std::string GameState::get_id() { return id_; }

void GameState::set_phase(Phase phase) { this->phase_ = phase; }

Phase GameState::get_phase() { return phase_; }

std::vector<Player*> GameState::get_players() {return players_;}

Player* GameState::get_player_by_id(std::string id_) {
    for(auto player : players_) {
        if(player->get_id() == id_) {
            return player;
        }
    }
    return nullptr;
}

bool GameState::add_player(Player* player) {
    if(!is_full()){
        for(auto player_ : players_) {
            if(player_->get_id() == player->get_id()) {
                return false;
            }
        }
        players_.push_back(player);
        return true;
    }
    return false;
}

bool GameState::remove_player(Player* player) {
    if(players_.size() == 0) {
        return false;
    }
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