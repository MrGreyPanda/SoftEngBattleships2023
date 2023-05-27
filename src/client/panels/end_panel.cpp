#include "end_panel.h"

#include "game_controller.h"

GameState* EndPanel::game_state_ = nullptr;

SDLGui::TextWidget* EndPanel::winner_or_loser_text_ = nullptr;
SDLGui::GridWidget* EndPanel::enemy_grid_ = nullptr;
std::array<SDLGui::DraggableImageWidget*, 5> EndPanel::enemy_ship_widget_arr_ = 
    { nullptr, nullptr, nullptr, nullptr, nullptr };

void EndPanel::init() {

    SDLGui::SDLGuiContext* end_panel_context =
        new SDLGui::SDLGuiContext("end_window");

    SDLGui::ImageWidget* background_image = new SDLGui::ImageWidget(
        "background_image", "../assets/background_img.bmp", -.1f, .0f, 1.3f,
        1.f, 0.,
        SDLGui::ImageFlagsExt_CenterImageVertical |
            SDLGui::ImageFlagsExt_CenterImageHorizontal |
            SDLGui::ImageFlagsExt_NoBackground);
    end_panel_context->addWidget(background_image);

    winner_or_loser_text_ = new SDLGui::TextWidget(
        "winner_or_loser_text", "You Lost!", 0, .06f, .1f, .4f, .09f, 0.,
        SDLGui::TextFlagsExt_CenterTextVertical |
            SDLGui::TextFlagsExt_NoBackground);
    end_panel_context->addWidget(winner_or_loser_text_);

    SDLGui::TextButtonWidget* diconnect_button = new SDLGui::TextButtonWidget(
        "end_disconnect_button", "Disconnect", 0.15f, .3f, .3f, .15f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    end_panel_context->addWidget(diconnect_button);

    SDLGui::TextButtonWidget* play_again_button = new SDLGui::TextButtonWidget(
        "end_play_again_button", "Play Again", 0.15f, .6f, .3f, .15f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    end_panel_context->addWidget(play_again_button);

    enemy_grid_ = new SDLGui::GridWidget(
        "end_enemy_board", .55f, .05f, .4f, .8f, 0., 10, 10,
        SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    end_panel_context->addWidget(enemy_grid_);

    // All enemy ship widgets
    enemy_ship_widget_arr_[4] =
        new SDLGui::DraggableImageWidget(
            "enemy_carrier_ship", "../assets/carrier_red.bmp", .6f, .2f, .3f, .11f, 0.,
            5, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_ship_widget_arr_[4]);

    enemy_ship_widget_arr_[3] =
        new SDLGui::DraggableImageWidget(
            "enemy_battleship_ship", "../assets/battleship_red.bmp", .6f, .33f, .24f,
            .105f, 0., 4, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_ship_widget_arr_[3]);

    enemy_ship_widget_arr_[2] =
        new SDLGui::DraggableImageWidget(
            "enemy_cruiser_ship", "../assets/cruiser_red.bmp", .6f, .455f, .18f, .1f, 0.,
            3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_ship_widget_arr_[2]);

    enemy_ship_widget_arr_[1] =
        new SDLGui::DraggableImageWidget(
            "enemy_submarine_ship", "../assets/submarine_red.bmp", .6f, .575f, .18f, .1f,
            0., 3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_ship_widget_arr_[1]);

    enemy_ship_widget_arr_[0] =
        new SDLGui::DraggableImageWidget(
            "enemy_destroyer_ship", "../assets/destroyer_red.bmp", .6f, .695f, .14f, .1f,
            0., 2, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    end_panel_context->addWidget(enemy_ship_widget_arr_[0]);

    SDLGui::SDLGuiEnvironment::pushContext(end_panel_context);
}

void EndPanel::reset()
{
    enemy_grid_->reset();
    for (unsigned i = 0; i < 5; ++i)
        enemy_ship_widget_arr_[i]->reset();
}

void EndPanel::update_board()
{
    EnemyBoard& enemy_board = game_state_->get_players()[0]->get_enemy_board();
    for (int i = 0; i < 5; i++) {
        const Ship* ship = enemy_board.get_ship_by_index(i);
        if (!ship->get_is_horizontal()) enemy_ship_widget_arr_[i]->rotateNoGrab(270.);
        enemy_ship_widget_arr_[i]->resizeToFit(
            enemy_grid_, ship->get_x(),
            ship->get_y(), true);
        enemy_ship_widget_arr_[i]->disable();
    }
}

void EndPanel::render() {
    SDLGui::begin("end_window");

    if (game_state_->get_players().size() > 0 && game_state_->get_players()[0]->has_won){
        winner_or_loser_text_->updateText(64, 0, "You Won!");
    } else {
        winner_or_loser_text_->updateText(64, 0, "You Lost!");
    }

    if (SDLGui::TextButton("end_disconnect_button")) {
        GameController::disconnect_from_server();
    }

    if (SDLGui::TextButton("end_play_again_button")) {
        game_state_->reset_state();
        ClientNetworkManager::send_message(JoinRequest().to_string());
    }
    SDLGui::end();
}