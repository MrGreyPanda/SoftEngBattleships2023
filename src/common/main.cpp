#include <cstdint>
#include <cstdio>
#include <string>

#include "game_state/include/game_state.h"

int main(){
    printf("Hello World from Common!\n");
    // ShipCategory boat = Carrier;
    // Ship my_ship(boat);
    std::vector<std::string> player_ids;
    player_ids.push_back("Player1");
    player_ids.push_back("Player2");
    std::string game_id = "Game1";
    GameState myGamestate(game_id, player_ids);
    return 0;
}