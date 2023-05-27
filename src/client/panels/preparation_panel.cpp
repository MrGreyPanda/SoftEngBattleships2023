#include "preparation_panel.h"

#include "give_up_request.h"

GameState* PreparationPanel::game_state_              = nullptr;
unsigned short PreparationPanel::help_button_counter_ = 0;

SDLGui::GridWidget* PreparationPanel::preparation_grid_ = nullptr;
SDLGui::TextButtonWidget* PreparationPanel::ready_button_ = nullptr;
SDLGui::TextWidget* PreparationPanel::enemy_prepared_text_ = nullptr;

std::array<SDLGui::DraggableImageWidget*, 5> PreparationPanel::ships_widget_arr_ = 
    { nullptr, nullptr, nullptr, nullptr, nullptr };
std::array<Ship*, 5> PreparationPanel::ships_ptr_arr_ = 
    { nullptr, nullptr, nullptr, nullptr, nullptr };


void PreparationPanel::init() {
    SDLGui::SDLGuiContext* preparation_panel_context =
        new SDLGui::SDLGuiContext("preparation_panel_context");

    preparation_grid_ = new SDLGui::GridWidget(
        "preparation_grid", .07f, .05f, .4f, .8f, 0., 10, 10,
        SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    preparation_panel_context->addWidget(preparation_grid_);

    SDLGui::TextWidget* preparation_phase_title = new SDLGui::TextWidget(
        "preparation_title", "Preparation Phase", 0, .0f, .05f, .6f, .1f, 0.,
        SDLGui::TextFlagsExt_CenterText |
            SDLGui::TextFlagsExt_CenterHorizontal);
    preparation_panel_context->addWidget(preparation_phase_title);

    ready_button_ = new SDLGui::TextButtonWidget(
        "ready_button", "Ready", 0.f, .88f, .4f, .08f, 0.f,
        SDLGui::TextButtonFlagsExt_CenterHorizontal |
            SDLGui::TextButtonFlagsExt_CenterText);
    preparation_panel_context->addWidget(ready_button_);

    ships_widget_arr_[0] =
        new SDLGui::DraggableImageWidget(
            "carrier_ship", "../assets/carrier.bmp", .6f, .2f, .3f, .11f, 0.,
            5, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(ships_widget_arr_[0]);

    ships_widget_arr_[1] =
        new SDLGui::DraggableImageWidget(
            "battleship_ship", "../assets/battleship.bmp", .6f, .33f, .24f,
            .105f, 0., 4, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(ships_widget_arr_[1]);

    ships_widget_arr_[2] =
        new SDLGui::DraggableImageWidget(
            "cruiser_ship", "../assets/cruiser.bmp", .6f, .455f, .18f, .1f, 0.,
            3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(ships_widget_arr_[2]);

    ships_widget_arr_[3] =
        new SDLGui::DraggableImageWidget(
            "submarine_ship", "../assets/submarine.bmp", .6f, .575f, .18f, .1f,
            0., 3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(ships_widget_arr_[3]);

    ships_widget_arr_[4] =
        new SDLGui::DraggableImageWidget(
            "destroyer_ship", "../assets/destroyer.bmp", .6f, .695f, .14f, .1f,
            0., 2, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(ships_widget_arr_[4]);

    SDLGui::HelpMarkerWidget* preparation_help = new SDLGui::HelpMarkerWidget(
        "preparation_help", "?", .85f, .05f, .1f, .05f, 0.,
        SDLGui::HelpMarkerFlagsExt_CenterText);
    preparation_help->addHelperText(
        "Press and hold on a ship to move it to the grid, and release to "
        "place it. Press R while holding a ship to rotate it",
        32, .3f, .3f, SDLGui::TextFlagsExt_CenterText);
    preparation_panel_context->addWidget(preparation_help);

    SDLGui::TextButtonWidget* disconnect_button = new SDLGui::TextButtonWidget(
        "resign_button", "Surrender", 0.05f, .05f, .1f, .05f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    preparation_panel_context->addWidget(disconnect_button);

    enemy_prepared_text_ = new SDLGui::TextWidget(
        "enemy_prepared_text", "Second player is preparing...", 0, .06f, .82f,
        .33f, .06f, 0.,
        SDLGui::TextFlagsExt_CenterHorizontal |
            SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterText);
    preparation_panel_context->addWidget(enemy_prepared_text_);

    SDLGui::pushContext(preparation_panel_context);
}

void PreparationPanel::reset()
{
    //Update the widgets
    preparation_grid_->reset();
    ready_button_->enable();
    ships_widget_arr_[0]->reset();
    ships_widget_arr_[1]->reset();
    ships_widget_arr_[2]->reset();
    ships_widget_arr_[3]->reset();
    ships_widget_arr_[4]->reset();
    enemy_prepared_text_->updateText(32, 0, "Second player is preparing...");

}

void PreparationPanel::update_board()
{
    OwnBoard& own_board = 
        game_state_->get_players()[0]->get_own_board();
    own_board.reset();
    ships_ptr_arr_[0] = own_board.get_ship_by_name(Carrier);
    ships_ptr_arr_[1] = own_board.get_ship_by_name(Battleship);
    ships_ptr_arr_[2] = own_board.get_ship_by_name(Cruiser);
    ships_ptr_arr_[3] = own_board.get_ship_by_name(Submarine);
    ships_ptr_arr_[4] = own_board.get_ship_by_name(Destroyer);
    game_state_->get_players()[0]->get_enemy_board().reset();
}

void PreparationPanel::render() {
    SDLGui::begin("preparation_panel_context");

    static std::pair<uint32_t, uint32_t> grid_cell_coords;
    static std::pair<float, float> image_position;

    OwnBoard& own_board =
        game_state_->get_players()[0]->get_own_board();

    // Because we should code DRY
    for (int i = 0; i < 5; i++) {
        ShipCategory ship_name = ships_ptr_arr_[i]->get_name();
        if (ships_widget_arr_[i]->isGrabbed()) {
            if (preparation_grid_->isHovered()) {
                grid_cell_coords = preparation_grid_->getHoverIndices();
                ships_widget_arr_[i]->resizeToFit(preparation_grid_, grid_cell_coords.first,
                                                 grid_cell_coords.second,
                                                 false);
            }
        }

        if(ships_widget_arr_[i]->onDrop()){
            if(!preparation_grid_->isHovered()){
                ships_widget_arr_[i]->reset();
                own_board.riddle_the_shiple(ship_name);
                ships_ptr_arr_[i]->reset_ship();
            }
            else{
                image_position = ships_widget_arr_[i]->getPosition();
                grid_cell_coords = preparation_grid_->getHoverIndices();
                ships_ptr_arr_[i]->set_is_horizontal(
                    !ships_widget_arr_[i]->isRotated());
                bool can_be_placed = own_board.is_valid_placement(
                    grid_cell_coords.first, grid_cell_coords.second,
                    *ships_ptr_arr_[i]);
                if (can_be_placed) {
                    ships_widget_arr_[i]->resizeToFit(
                        preparation_grid_, grid_cell_coords.first, grid_cell_coords.second,
                        true);
                    own_board.place_ship(grid_cell_coords.first,
                                         grid_cell_coords.second,ships_ptr_arr_[i]->get_is_horizontal(),
                                         ships_ptr_arr_[i]->get_name());
                } else {
                    ships_widget_arr_[i]->reset();
                    ships_ptr_arr_[i]->reset_ship();
                    own_board.riddle_the_shiple(ship_name);
                }
            }
        }
    }

    if (SDLGui::TextButton("ready_button")) {
        SDLGui::TextButton("ready_button").disable();
        Player* player = game_state_->get_players()[0];
        if (own_board.is_valid_configuration()) {
            ClientNetworkManager::send_message(
                PreparedRequest(game_state_->get_id(), player->get_id(),
                                own_board.get_ship_configuration())
                    .to_string());
        } else {
            own_board.reset();
            for (int i = 0; i < 5; i++) {
                ships_widget_arr_[i]->reset();
            SDLGui::TextButton("ready_button").enable();
            }
        }
    }

    if (game_state_->get_players()[1]->get_is_prepared()) {
        SDLGui::Text("enemy_prepared_text")
            .updateText(32, 0, "Second player is prepared!");
    }

    if (SDLGui::TextButton("resign_button")) {
        ClientNetworkManager::send_message(
            GiveUpRequest(game_state_->get_id(),
                          game_state_->get_players()[0]->get_id())
                .to_string());
    }

    SDLGui::end();
}