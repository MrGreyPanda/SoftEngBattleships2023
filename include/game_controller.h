#pragma once

#include <cassert>

#include "SDLGui.hpp"
#include "game_window.h"

class GameController {
   public:
    static void init();
    static void run();

   private:
    static void render();
};
