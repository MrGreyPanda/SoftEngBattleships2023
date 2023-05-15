#pragma once

#include "SDLGui.hpp"

#include "client_network_manager.h"

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
    static char m_server_address_input[33];
    static char m_server_address[33];
    static uint16_t m_server_port;
};