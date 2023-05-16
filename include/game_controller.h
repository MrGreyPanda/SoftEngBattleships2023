#pragma once

#include <cassert>

#include "SDLGui.hpp"
#include "game_state.h"
#include "connection_panel.h"
#include "preparation_panel.h"

class GameController {
   public:
    static void init();
    static void run();

   private:
    static void render();

    static GameState game_state;
};
