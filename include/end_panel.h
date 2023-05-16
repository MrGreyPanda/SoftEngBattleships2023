#pragma once

#include "SDLGui.hpp"
#include <string>
#include "game_state.h"


class EndPanel {
public:
    /// @brief Initializes all the widgets in the window
    static void init();

    /// @brief Renders the end window and processes user interaction
    static void render();

    // /// @brief Sets the winner of the game
    // static void set_winner(std::string winner);

    static void set_game_state(GameState* game_state) { game_state_ = game_state; };
private:
    static GameState* game_state_;
};