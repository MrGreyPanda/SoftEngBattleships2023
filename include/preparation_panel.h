#pragma once

#include <string>

#include "SDLGui.hpp"
#include "client_network_manager.h"
#include "game_state.h"
#include "prepared_request.h"

#include "battle_panel.h"

class PreparationPanel {
   public:

   /**
    * @brief Initializes all the widgets in the window
   */
    static void init();

    /**
     * @resets the widgets in the window
    */
    static void reset();

    /**
     * @brief updates the board according to the game state
    */
    static void update_board();

    /**
     * @brief Main rendering loop for the preparation panel
    */
    static void render();

    static void set_game_state(GameState* game_state) {
        game_state_ = game_state;
    };

   private:
    static GameState* game_state_;
    static unsigned short help_button_counter_;

    // Store the GUI Widgets that need to be reset
    // as static members
    static SDLGui::GridWidget* preparation_grid_;
    static SDLGui::TextButtonWidget* ready_button_;
    static SDLGui::TextWidget* enemy_prepared_text_;

    static std::array<SDLGui::DraggableImageWidget*, 5> ships_widget_arr_;
    static std::array<Ship*, 5> ships_ptr_arr_;
};