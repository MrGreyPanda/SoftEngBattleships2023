#include "game_state.h"

#include "helper_functions.h"

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
    : id(HelperFunctions::create_random_id()),
      phase(Lobby),
      turn_player_index(0),
      players({}) {}

GameState::GameState(std::string id, std::vector<Player*> players)
    : id(id), phase(Lobby), turn_player_index(0), players(players) {
    ships.push_back(Ship(Destroyer));
    ships.push_back(Ship(Submarine));
    ships.push_back(Ship(Cruiser));
    ships.push_back(Ship(Battleship));
    ships.push_back(Ship(Carrier));
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

std::string GameState::get_id() { return id; }

void GameState::set_phase(Phase phase) { this->phase = phase; }

Phase GameState::get_phase() { return phase; }

std::vector<Player*> GameState::get_players() {return players;}

bool GameState::add_player(Player* player) {
    if(!is_full()) {
        players.push_back(player);
        return true;
    }
    return false;
}

bool GameState::remove_player(Player* player) {
    if(players.at(0) == player) {
        players.erase(players.begin());
        return true;
    } else if(players.at(1) == player) {
        players.erase(players.begin()+1);
        return true;
    }
    return false;
}

bool GameState::is_full() {
    if(players.size() >= 2) {
        return true;
    }
    return false;
}

unsigned short GameState::get_turn_player_index() { return turn_player_index; }

void GameState::change_turn_player_index() {
    turn_player_index = (turn_player_index + 1) % players.size();
}