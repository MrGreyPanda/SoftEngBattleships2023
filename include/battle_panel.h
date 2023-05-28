#pragma once
#include <string>

#include "SDLGui.hpp"
#include "client_network_manager.h"
#include "game_state.h"
#include "give_up_request.h"
#include "shoot_request.h"
class BattlePanel {
   public:
    /**
     * @brief Initializes all the widgets in the window
     */
    static void init();

    /**
     * @brief Resets the widgets in the window
     */
    static void reset();

    /**
     * @brief updates the board according to the game state
     */
    static void update_board();

    /**
     * @brief Main rendering loop for the battle panel
     */
    static void render();

    /**
     * @brief Handles the shots
     * Just here to make the code more readable
     */
    static void handle_shots();

    /**
     * @brief Sets player pointer
     * @param player
     */
    static void set_player_ptr(Player* player);

    /**
     * @brief Sets game state
     * @param game_state
     */
    static void set_game_state(GameState* game_state);

   private:
    static GameState* game_state_;
    static Player* player_;
    static unsigned short help_button_counter_;

    static SDLGui::GridWidget* own_board_;
    static SDLGui::GridWidget* enemy_board_;
    static SDLGui::TextWidget* turn_message_text_;
    static std::array<SDLGui::DraggableImageWidget*, 5> ship_widget_arr_;
    static std::array<SDLGui::DraggableImageWidget*, 5> enemy_ship_widget_arr_;
    static std::array<bool, 5> enemy_ships_sunk_bool_;
};