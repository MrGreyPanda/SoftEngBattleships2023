#pragma once

#include <cassert>

#include "SDLGui.hpp"
#include "connection_panel.h"

class GameController {
   public:
    static void init();
    static void run();

   private:
    static void render();
};
