#pragma once

#include "SDLGui.hpp"
#include <string>


class EndPanel {
public:
    /// @brief Initializes all the widgets in the window
    static void init();

    /// @brief Renders the end window and processes user interaction
    static void render();

    // /// @brief Sets the winner of the game
    // static void set_winner(std::string winner);
};