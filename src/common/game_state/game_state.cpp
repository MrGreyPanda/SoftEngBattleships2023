#include "include/game_state.h"

#include "../helpers/random_id.h"

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

GameState::GameState()
    : id(create_random_id()),
      phase(Lobby),
      turn_player_index(0),
      players(std::vector<Player>(0)) {}

GameState::GameState(std::string id, std::vector<Player> players)
    : id(id), phase(Lobby), turn_player_index(0), players(players) {
    ships.push_back(Ship(Destroyer));
    ships.push_back(Ship(Submarine));
    ships.push_back(Ship(Cruiser));
    ships.push_back(Ship(Battleship));
    ships.push_back(Ship(Carrier));
}

GameState::GameState(std::string id, std::vector<std::string> player_ids)
    : id(id), phase(Lobby), turn_player_index(0) {
    for (auto player_id : player_ids) {
        players.push_back(Player(player_id));
    }
    ships.push_back(Ship(Destroyer));
    ships.push_back(Ship(Submarine));
    ships.push_back(Ship(Cruiser));
    ships.push_back(Ship(Battleship));
    ships.push_back(Ship(Carrier));
}

GameState::~GameState() {}

std::string GameState::get_id() { return id; }

void GameState::set_phase(Phase phase) { this->phase = phase; }

Phase GameState::get_phase() { return phase; }

unsigned short GameState::get_turn_player_index() { return turn_player_index; }

void GameState::change_turn_player_index() {
    turn_player_index = (turn_player_index + 1) % players.size();
}