#include "game_state.h"

#include "helper_functions.h"

GameState::GameState()
    : id_(HelperFunctions::create_random_id()),
      phase_(Lobby),
      turn_player_index_(0),
      players_({}) {}

GameState::GameState(std::string id, std::vector<Player*> players)
    : id_(id), phase_(Lobby), turn_player_index_(0), players_(players){}

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

std::string GameState::get_player_id_by_index(unsigned short index) {
    if(index < players_.size()) {
        return players_[index]->get_id();
    }
    return "";
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


bool GameState::start_game(){
    if(players_.size() < 2) {
        return false;
    }
    phase_ = Preparation;
    return true;
}

std::string GameState::get_other_player_id(std::string id) {
    bool is_found = false;
    for(auto player : players_) {
        if(player->get_id() == id_) {
            is_found = true;
        }
    }
    if(is_found) { 
        for(auto player : players_) {
            if(player->get_id() != id_) {
                return player->get_id();
            }
        }
    }

    return "";
}

