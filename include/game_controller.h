#pragma once

#include <cassert>

#include "SDLGui.hpp"
#include "game_state.h"
#include "client_response_message_handler.h"
#include "connection_panel.h"
#include "preparation_panel.h"
#include "battle_panel.h"
#include "end_panel.h"

class GameController {
   public:
    static void init();
    static void run();

    static std::string get_player_id();
    static void set_player_id(std::string player_id);

   private:
    static void render();

    static GameState game_state_;

    //static std::string game_player_id_;   // get player_id in connection panel.
};
