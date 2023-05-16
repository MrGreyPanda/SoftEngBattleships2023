#pragma once

#include <string>
#include <regex>

#include "SDLGui.hpp"

#include "client_network_manager.h"
#include "join_request.h"
<<<<<<< HEAD
#include "game_state.h"
=======
>>>>>>> be59a823f179c0e83cccf06fc0595f86d43fafad

class ConnectionPanel {
public:
    /// @brief Initializes all the widgets in the window
    static void init();

    /// @brief Renders the connection window and processes user interaction
    static void render();

    static void set_game_state(GameState* game_state) { game_state_ = game_state; };
private:
    /// @brief Checks the validity of the given server address
    static bool check_server_address();
private:
    static std::string server_address_input_;
    static std::string server_address_;
    static uint16_t server_port_;

    static GameState* game_state_;
};