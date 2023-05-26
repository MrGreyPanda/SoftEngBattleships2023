#include "preparation_panel.h"

#include "give_up_request.h"

GameState* PreparationPanel::game_state_              = nullptr;
unsigned short PreparationPanel::help_button_counter_ = 0;

bool PreparationPanel::was_reset = false;

void PreparationPanel::init() {
    // game_state_->reset_state();
    std::cout << "Initializing prep panel" << std::endl;
    SDLGui::SDLGuiContext* preparation_panel_context =
        new SDLGui::SDLGuiContext("preparation_panel_context");

    SDLGui::GridWidget* preparation_grid = new SDLGui::GridWidget(
        "preparation_grid", .07f, .05f, .4f, .8f, 0., 10, 10,
        SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    preparation_panel_context->addWidget(preparation_grid);

    SDLGui::TextWidget* preparation_phase_title = new SDLGui::TextWidget(
        "preparation_title", "Preparation Phase", 0, .0f, .05f, .6f, .1f, 0.,
        SDLGui::TextFlagsExt_CenterText |
            SDLGui::TextFlagsExt_CenterHorizontal);
    preparation_panel_context->addWidget(preparation_phase_title);

    SDLGui::TextButtonWidget* ready_button = new SDLGui::TextButtonWidget(
        "ready_button", "Ready", 0.f, .88f, .4f, .08f, 0.f,
        SDLGui::TextButtonFlagsExt_CenterHorizontal |
            SDLGui::TextButtonFlagsExt_CenterText);
    preparation_panel_context->addWidget(ready_button);

    SDLGui::DraggableImageWidget* carrier_ship =
        new SDLGui::DraggableImageWidget(
            "carrier_ship", "../assets/carrier.bmp", .6f, .2f, .3f, .11f, 0.,
            5, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(carrier_ship);
    carrier_ship->reset();

    SDLGui::DraggableImageWidget* battleship_ship =
        new SDLGui::DraggableImageWidget(
            "battleship_ship", "../assets/battleship.bmp", .6f, .33f, .24f,
            .105f, 0., 4, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(battleship_ship);
    battleship_ship->reset();

    SDLGui::DraggableImageWidget* cruiser_ship =
        new SDLGui::DraggableImageWidget(
            "cruiser_ship", "../assets/cruiser.bmp", .6f, .455f, .18f, .1f, 0.,
            3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(cruiser_ship);
    cruiser_ship->reset();

    SDLGui::DraggableImageWidget* submarine_ship =
        new SDLGui::DraggableImageWidget(
            "submarine_ship", "../assets/submarine.bmp", .6f, .575f, .18f, .1f,
            0., 3, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(submarine_ship);
    submarine_ship->reset();  // does not work, ship is still at the same place

    SDLGui::DraggableImageWidget* destroyer_ship =
        new SDLGui::DraggableImageWidget(
            "destroyer_ship", "../assets/destroyer.bmp", .6f, .695f, .14f, .1f,
            0., 2, 1,
            SDLGui::DraggableImageFlagsExt_CenterImage |
                SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(destroyer_ship);
    destroyer_ship->reset();

    /*SDLGui::TextButtonWidget* help_button = new SDLGui::TextButtonWidget(
        "help_button", "?", 0.85f, .05f, .1f, .05f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    preparation_panel_context->addWidget(help_button);

    SDLGui::TextWidget* help_message_text = new SDLGui::TextWidget(
        "help_message_text", "", .01f, .1f, .8f, .8f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterHorizontal);
    preparation_panel_context->addWidget(help_message_text);*/

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

    SDLGui::TextWidget* enemy_prepared_text = new SDLGui::TextWidget(
        "enemy_prepared_text", "Second player is preparing...", 0, .06f, .82f,
        .33f, .06f, 0.,
        SDLGui::TextFlagsExt_CenterHorizontal |
            SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterText);
    preparation_panel_context->addWidget(enemy_prepared_text);

    SDLGui::pushContext(preparation_panel_context);
    std::cout << "Finished initializing the prep panel" << std::endl;
}

void PreparationPanel::render() {
    SDLGui::begin("preparation_panel_context");
    static OwnBoard& own_board =
        game_state_->get_players()[0]->get_own_board();

    // Static function bound members (first) initialization
    static SDLGui::DraggableImageWidget& carrier_widget =
        SDLGui::DraggableImage("carrier_ship");
    static SDLGui::DraggableImageWidget& battleship_widget =
        SDLGui::DraggableImage("battleship_ship");
    static SDLGui::DraggableImageWidget& cruiser_widget =
        SDLGui::DraggableImage("cruiser_ship");
    static SDLGui::DraggableImageWidget& submarine_widget =
        SDLGui::DraggableImage("submarine_ship");
    static SDLGui::DraggableImageWidget& destroyer_widget =
        SDLGui::DraggableImage("destroyer_ship");
    
    static SDLGui::GridWidget& grid = SDLGui::Grid("preparation_grid");

    static Ship* carrier    = own_board.get_ship_by_name(Carrier);
    static Ship* battleship = own_board.get_ship_by_name(Battleship);
    static Ship* cruiser    = own_board.get_ship_by_name(Cruiser);
    static Ship* submarine  = own_board.get_ship_by_name(Submarine);
    static Ship* destroyer  = own_board.get_ship_by_name(Destroyer);

    static std::array<SDLGui::DraggableImageWidget*, 5> ships_widget_arr = {
        destroyer_widget.getPtr(), submarine_widget.getPtr(), cruiser_widget.getPtr(),
        battleship_widget.getPtr(), carrier_widget.getPtr()};
    static std::array<Ship*, 5> ships_ptr_arr = {destroyer, submarine, cruiser,
                                          battleship, carrier};

    if (!was_reset) {
        // reset stuff
        // Static function bound members update
        SDLGui::TextButton("ready_button").enable();
        carrier_widget.reset();
        battleship_widget.reset();
        cruiser_widget.reset();
        submarine_widget.reset();
        destroyer_widget.reset();
        grid.reset();
        grid.enable();
        SDLGui::Text("enemy_prepared_text")
            .updateText(32, 0, "Second player is preparing...");
        
        own_board.reset();
        carrier    = own_board.get_ship_by_name(Carrier);
        battleship = own_board.get_ship_by_name(Battleship);
        cruiser    = own_board.get_ship_by_name(Cruiser);
        submarine  = own_board.get_ship_by_name(Submarine);
        destroyer  = own_board.get_ship_by_name(Destroyer);
        game_state_->get_players()[0]->get_enemy_board().reset();

        ships_ptr_arr[0] = destroyer;
        ships_ptr_arr[1] = submarine;
        ships_ptr_arr[2] = cruiser;
        ships_ptr_arr[3] = battleship;
        ships_ptr_arr[4] = carrier;

        was_reset = true;
    }

    static std::pair<uint32_t, uint32_t> grid_cell_coords;
    static SDL_FRect grid_hover_cell_data;
    static std::pair<float, float> image_position;

    // Because we should code DRY
    for (int i = 0; i < 5; i++) {
        ShipCategory ship_name = ships_ptr_arr[i]->get_name();
        if (ships_widget_arr[i]->isGrabbed()) {
            if (grid.isHovered()) {
                grid_cell_coords = grid.getHoverIndices();
                ships_widget_arr[i]->resizeToFit(&grid, grid_cell_coords.first,
                                                 grid_cell_coords.second,
                                                 false);
            }
        }

        if(ships_widget_arr[i]->onDrop()){
            if(!grid.isHovered()){
                ships_widget_arr[i]->reset();
                own_board.riddle_the_shiple(ship_name);
                ships_ptr_arr[i]->reset_ship();
            }
            else{
                image_position = ships_widget_arr[i]->getPosition();
                grid_cell_coords = grid.getHoverIndices();
                ships_ptr_arr[i]->set_is_horizontal(
                    !ships_widget_arr[i]->isRotated());
                bool can_be_placed = own_board.is_valid_placement(
                    grid_cell_coords.first, grid_cell_coords.second,
                    *ships_ptr_arr[i]);
                if (can_be_placed) {
                    ships_widget_arr[i]->resizeToFit(
                        &grid, grid_cell_coords.first, grid_cell_coords.second,
                        true);
                    own_board.place_ship(grid_cell_coords.first,
                                         grid_cell_coords.second,ships_ptr_arr[i]->get_is_horizontal(),
                                         ships_ptr_arr[i]->get_name());
                } else {
                    ships_widget_arr[i]->reset();
                    ships_ptr_arr[i]->reset_ship();
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
                ships_widget_arr[i]->reset();
            }
        }
    }

    /*if (SDLGui::TextButton("help_button")) {
        if (help_button_counter_ == 0) {
            ++help_button_counter_;
            // Set the background
            SDLGui::Text("help_message_text")
                .updateText(512,
                            "Press R while holding a ship to rotate it. Click "
                            "on the help button to close this message.");
        } else {
            --help_button_counter_;
            // Set the background to nothing
            SDLGui::Text("help_message_text").updateText(512, "");
        }
    }*/

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