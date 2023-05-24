#pragma once

#include <string>

#include "SDLGui.hpp"

#include "game_state.h"
#include "client_network_manager.h"
#include "ready_request.h"
#include "preparation_panel.h"

class LobbyPanel {
public:
    /// @brief Initializes all the widgets in the window
    static void init();

    /// @brief Renders the connection window and processes user interaction
    static void render();

    static void set_game_state(GameState* game_state) { game_state_ = game_state; };
private:
    /// @brief Checks if game is full
    static bool check_is_full();
private:

    static GameState* game_state_;
};