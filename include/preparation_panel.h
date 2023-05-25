#pragma once

#include <string>

#include "SDLGui.hpp"
#include "client_network_manager.h"
#include "game_state.h"
#include "prepared_request.h"

#include "battle_panel.h"

class PreparationPanel {
   public:
    static void init();

    static void render();

    static void set_game_state(GameState* game_state) {
        game_state_ = game_state;
    };

    static bool was_reset;

   private:
    static GameState* game_state_;
    static unsigned short help_button_counter_;
};