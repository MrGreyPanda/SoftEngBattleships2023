#pragma once

#include "SDLGui.hpp"

class ConnectionWindow {
public:
    static void init();

    static void render();
private:
    static char m_serverAddress[20];
    static uint16_t m_serverPort;
};