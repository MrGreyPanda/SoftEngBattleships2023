#pragma once
#include <string>

#include "SDLGui.hpp"

#include "shoot_request.h"
#include "client_network_manager.h"
#include "game_state.h"
class BattlePanel {
public:
    static void init();

    static void render();

    static void handle_shots();

    static void set_player_id(std::string player_id);

    static void set_game_state(GameState* game_state);
private:
    static GameState* game_state_;
    static std::string game_player_id_;
};