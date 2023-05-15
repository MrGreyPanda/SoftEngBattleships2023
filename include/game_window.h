#pragma once

#include <string>
#include <regex>

#include "SDLGui.hpp"

#include "client_network_manager.h"
#include "requests/client_join_request.h"

class ConnectionWindow {
public:
    /// @brief Initializes all the widgets in the window
    static void init();

    /// @brief Renders the connection window and processes user interaction
    static void render();
private:
    /// @brief Checks the validity of the given server address
    static bool check_server_address();
private:
    static std::string server_address_input_;
    static std::string server_address_;
    static uint16_t server_port_;
};