#include "end_panel.h"

GameState* EndPanel::game_state_ = nullptr;
bool EndPanel::was_reset = false;

void EndPanel::init() {
    static SDL_FRect grid_hover_cell_data;
    SDLGui::SDLGuiContext* end_panel_context =
        new SDLGui::SDLGuiContext("end_window");

    SDLGui::TextWidget* winner_or_loser_text = new SDLGui::TextWidget(
        "winner_or_loser_text", "", 0, .06f, .1f, .4f, .09f, 0.,
        SDLGui::TextFlagsExt_CenterTextVertical |
            SDLGui::TextFlagsExt_NoBackground);
    end_panel_context->addWidget(winner_or_loser_text);

    SDLGui::TextButtonWidget* diconnect_button = new SDLGui::TextButtonWidget(
        "end_disconnect_button", "Disconnect", 0.15f, .3f, .3f, .15f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    end_panel_context->addWidget(diconnect_button);

    SDLGui::TextButtonWidget* play_again_button = new SDLGui::TextButtonWidget(
        "end_play_again_button", "Play Again", 0.15f, .6f, .3f, .15f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    end_panel_context->addWidget(play_again_button);

    static SDLGui::GridWidget* end_enemy_board = new SDLGui::GridWidget(
        "end_enemy_board", .55f, .05f, .4f, .8f, 0., 10, 10,
        SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    end_panel_context->addWidget(end_enemy_board);

    // EnemyBoard enemy_board = game_state_->get_players()[0]->get_enemy_board();
    // unsigned short grid_size =
    //     game_state_->get_players()[0]->get_enemy_board().get_grid_size();
    // for (int i = 0; i < grid_size; i++) {
    //     for (int j = 0; j < grid_size; j++) {
    //         unsigned short grid_value = enemy_board.get_grid_value(i, j);
    //         bool was_shot             = enemy_board.get_is_shot(i, j);
    //         if (grid_value > 0 && grid_value < 6) {
    //             if (was_shot) {
    //                 end_enemy_board->completeCell(i,j);
    //             } else {
    //                 end_enemy_board->setCell(i,j, true);
    //             }
    //         }
    //     }
    // }

    SDLGui::DraggableImageWidget* enemy_carrier_ship =
        new SDLGui::DraggableImageWidget(
            "enemy_carrier_ship", "../assets/carrier.bmp", .6f, .2f, .3f, .11f, 0.,
            5, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_carrier_ship);
    enemy_carrier_ship->reset();

    SDLGui::DraggableImageWidget* enemy_battleship_ship =
        new SDLGui::DraggableImageWidget(
            "enemy_battleship_ship", "../assets/battleship.bmp", .6f, .33f, .24f,
            .105f, 0., 4, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_battleship_ship);
    enemy_battleship_ship->reset();

    SDLGui::DraggableImageWidget* enemy_cruiser_ship =
        new SDLGui::DraggableImageWidget(
            "enemy_cruiser_ship", "../assets/cruiser.bmp", .6f, .455f, .18f, .1f, 0.,
            3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_cruiser_ship);
    enemy_cruiser_ship->reset();

    SDLGui::DraggableImageWidget* enemy_submarine_ship =
        new SDLGui::DraggableImageWidget(
            "enemy_submarine_ship", "../assets/submarine.bmp", .6f, .575f, .18f, .1f,
            0., 3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_submarine_ship);
    enemy_submarine_ship->reset();  // does not work, ship is still at the same place

    SDLGui::DraggableImageWidget* enemy_destroyer_ship =
        new SDLGui::DraggableImageWidget(
            "enemy_destroyer_ship", "../assets/destroyer.bmp", .6f, .695f, .14f, .1f,
            0., 2, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_destroyer_ship);
    enemy_destroyer_ship->reset();

    std::array<SDLGui::DraggableImageWidget*, 5> ship_widgets = {
    enemy_destroyer_ship, enemy_submarine_ship, enemy_cruiser_ship, enemy_battleship_ship,
    enemy_carrier_ship};

    EnemyBoard enemy_board = game_state_->get_players()[0]->get_enemy_board();
    for (int i = 0; i < 5; i++) {
        const Ship* ship = enemy_board.get_ship_by_index(i);
        // ship_widgets[i]->reset();
        // grid_hover_cell_data =
        //     end_enemy_board->getIndexCellCoordinates(ship->get_x(), ship->get_y());
        if (!ship->get_is_horizontal()) ship_widgets[i]->rotateNoGrab(270.);
        ship_widgets[i]->resizeToFit(
            end_enemy_board, ship->get_x(),
            ship->get_y(), true);
        ship_widgets[i]->disable();
    }

    SDLGui::SDLGuiEnvironment::pushContext(end_panel_context);
}

void EndPanel::render() {
    SDLGui::begin("end_window");

    if(!was_reset){
        was_reset = true;
    }

    if (game_state_->get_players()[0]->has_won) {
        SDLGui::Text("winner_or_loser_text").updateText(64, 0, "You Won!");
    } else {
        SDLGui::Text("winner_or_loser_text").updateText(64, 0, "You Lost!");
    }

    if (SDLGui::TextButton("end_play_again_button")) {
        game_state_->reset_state();
        ClientNetworkManager::send_message(JoinRequest().to_string());
    }
    SDLGui::end();
}