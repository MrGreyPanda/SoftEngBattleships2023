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
