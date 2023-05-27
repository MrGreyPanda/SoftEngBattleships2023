#pragma once
#include <string>

#include "SDLGui.hpp"

#include "shoot_request.h"
#include "client_network_manager.h"
#include "game_state.h"
#include "give_up_request.h"
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

    static void set_player_ptr(Player* player);

    static void set_game_state(GameState* game_state);


private:
    static GameState* game_state_;
    static Player* player_;
    static unsigned short help_button_counter_;

    static SDLGui::GridWidget* own_board_;
    static SDLGui::GridWidget* enemy_board_;
    static SDLGui::TextWidget* turn_message_text_;
    static std::array<SDLGui::DraggableImageWidget*, 5> ship_widget_arr_;
};