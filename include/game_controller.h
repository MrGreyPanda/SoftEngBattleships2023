#pragma once

#include <cassert>

#include "SDLGui.hpp"
#include "battle_panel.h"
#include "client_response_message_handler.h"
#include "connection_panel.h"
#include "end_panel.h"
#include "game_state.h"
#include "lobby_panel.h"
#include "preparation_panel.h"

class GameController {
   public:
    static void init();
    static void run();

    static std::string get_player_id();
    static void set_player_id(std::string player_id);

    static void disconnect_from_server();

   private:
    static void render();

    static GameState game_state_;

    // True if a panel is initialized, false otherwise
    static std::vector<bool> InitializedPannels_;

    // static std::string game_player_id_;   // get player_id in connection
    // panel.
};
