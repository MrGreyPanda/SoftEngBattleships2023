#pragma once

#include <cassert>

#include "SDLGui.hpp"

class GameController {
public:
    static void init();
    static void run();
private:
    static void render();
};
