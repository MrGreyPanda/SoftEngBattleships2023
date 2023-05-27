#pragma once

#include "SDLGui.hpp"
#include <string>
#include "game_state.h"
#include "client_network_manager.h"
#include "join_request.h"

#include "game_controller.h"

class EndPanel {
public:
    /// @brief Initializes all the widgets in the window
    static void init();

    static void reset();

    static void update_board();

    /// @brief Renders the end window and processes user interaction
    static void render();

    // /// @brief Sets the winner of the game
    // static void set_winner(std::string winner);

    static void set_game_state(GameState* game_state) { game_state_ = game_state; };

private:
    static GameState* game_state_;

    static SDLGui::TextWidget* winner_or_loser_text_;
    static SDLGui::GridWidget* enemy_grid_;
    static std::array<SDLGui::DraggableImageWidget*, 5> enemy_ship_widget_arr_;
};