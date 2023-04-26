#pragma once
#include "player.h"
#include <utility>
#include <vector>
#include <string>
/*
The class attributes are
id: string, unique game ID
players: vector<player*>, representing the players playing the current game
phase: int, number representing which phase the game is in (0) lobby (not started yet), (1) preparation phase, (2) battle phase, (3) game ended.
ships: vector, the ships agreed upon for this game
turn_player_index: unsigned short, the index of the player in the players array whose turn it is.
*/
enum Phase{
    Lobby = 0,
    Preparation = 1,
    Battle = 2,
    End = 3
};

class GameState {
public:
    GameState(std::string id, std::vector<Player*> players);
    

private:
    std::string id;
    std::vector<Player*> players;
    Phase phase;
    std::vector<Ship> ships;
    unsigned short turn_player_index;
};
