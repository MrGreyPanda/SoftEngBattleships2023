#pragma once

#include <regex>
#include <string>

#include "SDLGui.hpp"
#include "client_network_manager.h"
#include "game_state.h"
#include "join_request.h"

class ConnectionPanel {
   public:
    /**
     * @brief Initializes all the widgets in the window
     *
     */
    static void init();

    /**
     * @brief Renders the panel
     *
     */
    static void render();

    /**
     * @brief Set the game state object
     *
     * @param game_state
     */
    static void set_game_state(GameState* game_state) {
        game_state_ = game_state;
    };

   private:
    /// @brief Checks the validity of the given server address
    static bool is_valid_ip_address(const std::string&);

   private:
    static std::string server_address_input_;
    static std::string server_address_;
    static uint16_t server_port_;

    static GameState* game_state_;
};