#include "game_state.h"

// class GameState {
// public:
//     GameState(std::string id);
    

// private:
//     std::string id;
//     std::vector<Player*> players;
//     Phase phase;
//     std::vector<Ship> ships;
//     unsigned short turn_player_index;
// };

GameState::GameState(std::string id, std::vector<Player*> players) : id(id), phase(Lobby), turn_player_index(0), players(players) {
    ships.push_back(Ship("Destroyer", 2));
    ships.push_back(Ship("Submarine", 3));
    ships.push_back(Ship("Cruiser", 3));
    ships.push_back(Ship("Battleship", 4));
    ships.push_back(Ship("Carrier", 5));
}

GameState::~GameState(){
    for(auto player : players){
        delete player;
    }
}

std::string GameState::get_id(){
    return id;
}

void GameState::set_phase(Phase phase){
    this->phase = phase;
}

Phase GameState::get_phase(){
    return phase;
}

unsigned short GameState::get_turn_player_index(){
    return turn_player_index;
}

void GameState::change_turn_player_index(){
    turn_player_index = (turn_player_index + 1) % players.size();
}