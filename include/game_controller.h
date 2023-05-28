#pragma once

#include <cassert>

#include "SDLGui.hpp"
#include "battle_panel.h"
#include "client_response_message_handler.h"
#include "connection_panel.h"
#include "end_panel.h"
#include "game_state.h"
#include "lobby_panel.h"
#include "preparation_panel.h"

class GameController {
   public:
    /**
     * @brief Initializes the client
     *
     */
    static void init();
    /**
     * @brief Handles the running client
     *
     */
    static void run();

    /**
     * @brief Get the player id object
     *
     * @return std::string
     */
    static std::string get_player_id();

    /**
     * @brief Set the player id object
     *
     * @param player_id
     */
    static void set_player_id(std::string player_id);

    /**
     * @brief Disconnects from server
     *
     */
    static void disconnect_from_server();

   private:
    /**
     * @brief Renders the GUI
     *
     */
    static void render();

    static GameState game_state_;

    // True if a panel is initialized, false otherwise
    static std::vector<bool> InitializedPannels_;

    // static std::string game_player_id_;   // get player_id in connection
    // panel.
};
