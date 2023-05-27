#include "battle_panel.h"

GameState* BattlePanel::game_state_              = nullptr;
unsigned short BattlePanel::help_button_counter_ = 0;
Player* BattlePanel::player_                     = nullptr;
bool BattlePanel::was_reset                      = false;

SDLGui::GridWidget* BattlePanel::own_board_ = nullptr;
SDLGui::GridWidget* BattlePanel::enemy_board_ = nullptr;
SDLGui::TextWidget* BattlePanel::turn_message_text_ = nullptr;
std::array<SDLGui::DraggableImageWidget*, 5> BattlePanel::ship_widget_arr_ = 
    { nullptr, nullptr, nullptr, nullptr, nullptr };

void BattlePanel::init() {

    //set_player_ptr(game_state_->get_players()[0]);
    //OwnBoard* players_board = &player_->get_own_board();
    SDLGui::SDLGuiContext* battle_panel_context =
        new SDLGui::SDLGuiContext("battle_panel_context");

    own_board_ = new SDLGui::GridWidget(
        "own_board", .05f, .05f, .4f, .8f, 0., 10, 10,
        SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    battle_panel_context->addWidget(own_board_);

    enemy_board_ = new SDLGui::GridWidget(
        "enemy_board", .55f, .05f, .4f, .8f, 0., 10, 10,
        SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    battle_panel_context->addWidget(enemy_board_);

    SDLGui::TextWidget* battle_phase_title = new SDLGui::TextWidget(
        "battle_title", "Battle Phase", 0, .0f, .05f, .6f, .1f, 0.,
        SDLGui::TextFlagsExt_CenterText |
            SDLGui::TextFlagsExt_CenterHorizontal);
    battle_panel_context->addWidget(battle_phase_title);

    turn_message_text_ =
        new SDLGui::TextWidget("turn_message_text", "", 0, .0f, .9f, .3f, .1f, 0.,
                               SDLGui::TextFlagsExt_CenterTextHorizontal |
                                   SDLGui::TextFlagsExt_NoBackground |
                                   SDLGui::TextFlagsExt_CenterHorizontal);
    battle_panel_context->addWidget(turn_message_text_);

    SDLGui::TextButtonWidget* resign_button = new SDLGui::TextButtonWidget(
        "resign_button", "Surrender", 0.05f, .05f, .1f, .05f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    battle_panel_context->addWidget(resign_button);

    /*SDLGui::TextButtonWidget* help_button = new SDLGui::TextButtonWidget(
        "help_button", "?", 0.85f, .05f, .1f, .05f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    battle_panel_context->addWidget(help_button);

    SDLGui::TextWidget* help_message_text = new SDLGui::TextWidget(
        "help_message_text", "", 0, .01f, .1f, .8f, .8f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterHorizontal);
    battle_panel_context->addWidget(help_message_text);*/

    SDLGui::HelpMarkerWidget* battle_help = new SDLGui::HelpMarkerWidget(
        "battle_help", "?", .85f, .05f, .1f, .05f, 0.,
        SDLGui::HelpMarkerFlagsExt_CenterText);
    battle_help->addHelperText("Click on the enemy board to shoot. Click on the resign button to resign",
        32, .3f, .3f, SDLGui::TextFlagsExt_CenterText);
    battle_panel_context->addWidget(battle_help);

    /**
     * @brief The following widgets are used to display the ships that the
     * player has placed
     */
    ship_widget_arr_[4] =
        new SDLGui::DraggableImageWidget(
            "carrier_ship", "../assets/carrier.bmp", .6f, .2f, .3f, .12f, 0.,
            5, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    battle_panel_context->addWidget(ship_widget_arr_[4]);

    ship_widget_arr_[3] =
        new SDLGui::DraggableImageWidget(
            "battleship_ship", "../assets/battleship.bmp", .6f, .35f, .25f,
            .1f, 0., 4, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    battle_panel_context->addWidget(ship_widget_arr_[3]);

    ship_widget_arr_[2] =
        new SDLGui::DraggableImageWidget(
            "cruiser_ship", "../assets/cruiser.bmp", .6f, .5f, .2f, .08f, 0.,
            3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    battle_panel_context->addWidget(ship_widget_arr_[2]);

    ship_widget_arr_[1] =
        new SDLGui::DraggableImageWidget(
            "submarine_ship", "../assets/submarine.bmp", .6f, .65f, .2f, .08f,
            0., 3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    battle_panel_context->addWidget(ship_widget_arr_[1]);

    ship_widget_arr_[0] =
        new SDLGui::DraggableImageWidget(
            "destroyer_ship", "../assets/destroyer.bmp", .6f, .8f, .15f, .06f,
            0., 2, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    battle_panel_context->addWidget(ship_widget_arr_[0]);

    SDLGui::SDLGuiEnvironment::pushContext(battle_panel_context);
}

void BattlePanel::reset()
{
    own_board_->reset();
    enemy_board_->reset();

}

void BattlePanel::update_board()
{
    set_player_ptr(game_state_->get_players()[0]);

    player_->get_enemy_board().reset();

    for (int i = 0; i < 5; i++) {
        const Ship* ship = player_->get_own_board().get_ship_by_index(i);
        ship_widget_arr_[i]->reset();
        if (!ship->get_is_horizontal()) ship_widget_arr_[i]->rotateNoGrab(270.);
        ship_widget_arr_[i]->resizeToFit(
            own_board_, ship->get_x(), ship->get_y(), true);
        ship_widget_arr_[i]->disable();
    }
}

void BattlePanel::set_game_state(GameState* game_state) {
    game_state_ = game_state;
}

void BattlePanel::set_player_ptr(Player* player) { player_ = player; }

void BattlePanel::handle_shots() {
    std::pair<uint32_t, uint32_t> xy =
        SDLGui::Grid("enemy_board").getClickIndices();
    unsigned short x = (unsigned short)xy.first;
    unsigned short y = (unsigned short)xy.second;
    if (player_->is_valid_shot(x, y)) {
        // Send a shoot request to the server
        ShootRequest shoot_request(game_state_->get_id(), player_->get_id(), x,
                                   y);
        std::cout << "Sending shoot request\n";
        ClientNetworkManager::send_message(shoot_request.to_string());
        player_->has_shot = true;
    }
}

void BattlePanel::render() {
    SDLGui::begin("battle_panel_context");

    static unsigned short grid_size =
        player_->get_enemy_board().get_grid_size();
    static unsigned short grid_value;
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if (player_->get_enemy_board().get_is_shot(i, j)) {
                grid_value = player_->get_enemy_board().get_grid_value(i, j);
                if (grid_value == 6) {
                    enemy_board_->setCell(i, j, true);
                } else if (grid_value > 0 && grid_value < 6) {
                    enemy_board_->completeCell(i, j);
                } else if (grid_value == 0) {
                    enemy_board_->setCell(i, j, false);
                } else {
                    // Return error
                }
            }
            if (player_->get_own_board().get_is_shot(i, j)) {
                grid_value = player_->get_own_board().get_grid_value(i, j);
                if (grid_value > 0 && grid_value < 7) {
                    own_board_->setCell(i, j, true);
                } else if (grid_value == 0) {
                    own_board_->setCell(i, j, false);
                } else {
                    // Return error
                }
            }
        }
    }

    if (player_->is_own_turn) {
        /*if(Grid is enabled)*/
        turn_message_text_->updateText(64, 0, "It is your turn.");
        if (!player_->has_shot) {
            // std::cout << "It is your turn\n";
            if (SDLGui::Grid("enemy_board")) handle_shots();
        }

    } else {
        turn_message_text_
            ->updateText(64, 0, "It is the enemy' turn.");
    }

    if (SDLGui::TextButton("resign_button")) {
        // Send a resign request to the server -> Pop up a message box to
        // confirm
        GiveUpRequest resign_request(game_state_->get_id(), player_->get_id());
        ClientNetworkManager::send_message(resign_request.to_string());
    }

    SDLGui::end();
}