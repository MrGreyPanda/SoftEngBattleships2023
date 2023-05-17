#pragma once

#include "SDLGui.hpp"
#include <string>

#include "game_state.h"

class BattlePanel {
public:
    static void init();

    static void render();

    static void set_game_state(GameState* game_state) { game_state_ = game_state; };
private:
    static GameState* game_state_;
};