#pragma once
#include <string>

#include "SDLGui.hpp"

#include "shoot_request.h"
#include "client_network_manager.h"
#include "game_state.h"
#include "give_up_request.h"
class BattlePanel {
public:
    static void init();

    static void render();

    static void handle_shots();


    static void set_player_ptr(Player* player);

    static void set_game_state(GameState* game_state);

    static bool was_reset;

private:
    static GameState* game_state_;
    static Player* player_;
    static unsigned short help_button_counter_;
};