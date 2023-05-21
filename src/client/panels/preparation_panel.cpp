#include "preparation_panel.h"

GameState* PreparationPanel::game_state_ = nullptr;
unsigned short PreparationPanel::help_button_counter_ = 0;

void PreparationPanel::init()
{
    SDLGui::SDLGuiContext* preparation_panel_context = 
        new SDLGui::SDLGuiContext("preparation_panel_context");

    SDLGui::GridWidget* preparation_grid = 
        new SDLGui::GridWidget("preparation_grid", .07f, .05f, .4f, .8f,
        0., 10, 10, SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    preparation_panel_context->addWidget(preparation_grid);

    SDLGui::TextWidget* preparation_phase_title = 
        new SDLGui::TextWidget("preparation_title", "Preparation Phase",
        .0f, .05f, .6f, .1f, 0., SDLGui::TextFlagsExt_CenterText | 
        SDLGui::TextFlagsExt_CenterHorizontal);
        preparation_panel_context->addWidget(preparation_phase_title);

    SDLGui::TextButtonWidget* ready_button = 
        new SDLGui::TextButtonWidget("ready_button", "Ready", 0.f, .88f, .4f, .08f, 0.f,
        SDLGui::TextButtonFlagsExt_CenterHorizontal |
            SDLGui::TextButtonFlagsExt_CenterText);
    preparation_panel_context->addWidget(ready_button);

    SDLGui::DraggableImageWidget* carrier_ship = 
        new SDLGui::DraggableImageWidget("carrier_ship", "../assets/carrier.bmp",
        .6f, .2f, .3f, .11f, 0., 5, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage |
        SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(carrier_ship);
    
    SDLGui::DraggableImageWidget* battleship_ship = 
        new SDLGui::DraggableImageWidget("battleship_ship", "../assets/battleship.bmp",
        .6f, .33f, .24f, .105f, 0., 4, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage |
        SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(battleship_ship);
    
    SDLGui::DraggableImageWidget* cruiser_ship = 
        new SDLGui::DraggableImageWidget("cruiser_ship", "../assets/cruiser.bmp",
        .6f, .455f, .18f, .1f, 0., 3, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage |
        SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(cruiser_ship);
    
    SDLGui::DraggableImageWidget* submarine_ship = 
        new SDLGui::DraggableImageWidget("submarine_ship", "../assets/submarine.bmp",
        .6f, .575f, .18f, .1f, 0., 3, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage |
        SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(submarine_ship);

    SDLGui::DraggableImageWidget* destroyer_ship = 
        new SDLGui::DraggableImageWidget("destroyer_ship", "../assets/destroyer.bmp",
        .6f, .695f, .14f, .1f, 0., 2, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage |
        SDLGui::DraggableImageFlagsExt_NoBackground);
    preparation_panel_context->addWidget(destroyer_ship);

    SDLGui::TextButtonWidget* help_button = new SDLGui::TextButtonWidget(
        "helpButton", "?", 0.85f, .05f, .1f, .05f, 0.,
         SDLGui::TextButtonFlagsExt_CenterText);
    preparation_panel_context->addWidget(help_button);


    SDLGui::TextWidget* help_message_text = new SDLGui::TextWidget(
        "helpMessageText", "", .01f, .1f, .8f, .8f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterHorizontal);
    preparation_panel_context->addWidget(help_message_text);

    SDLGui::TextWidget* enemy_prepared_text =
        new SDLGui::TextWidget("enemy_prepared_text", "Second player is preparing...",
                               .06f, .82f, .33f, .06f, 0.,
                               SDLGui::TextFlagsExt_CenterHorizontal |
                                   SDLGui::TextFlagsExt_NoBackground | SDLGui::TextFlagsExt_CenterText);
    preparation_panel_context->addWidget(enemy_prepared_text);

    SDLGui::pushContext(preparation_panel_context);
}

void PreparationPanel::render()
{
    SDLGui::begin("preparation_panel_context");

    static OwnBoard& own_board = game_state_->get_players()[0]->get_own_board();
    if(own_board.has_been_reset)
        SDLGui::TextButton("ready_button").enable();

    static SDLGui::DraggableImageWidget& carrier_widget = SDLGui::DraggableImage("carrier_ship");
    static SDLGui::DraggableImageWidget& battleship_widget = SDLGui::DraggableImage("battleship_ship");
    static SDLGui::DraggableImageWidget& cruiser_widget = SDLGui::DraggableImage("cruiser_ship");
    static SDLGui::DraggableImageWidget& submarine_widget = SDLGui::DraggableImage("submarine_ship");
    static SDLGui::DraggableImageWidget& destroyer_widget = SDLGui::DraggableImage("destroyer_ship");

    Ship* carrier = own_board.get_ship_by_name(Carrier);
    Ship* battleship = own_board.get_ship_by_name(Battleship);
    Ship* cruiser = own_board.get_ship_by_name(Cruiser);
    Ship* submarine = own_board.get_ship_by_name(Submarine);
    Ship* destroyer = own_board.get_ship_by_name(Destroyer);

    std::array<SDLGui::DraggableImageWidget*, 5> ships_widget_arr = {&destroyer_widget, &submarine_widget, &cruiser_widget, &battleship_widget, &carrier_widget};
    std::array<Ship*, 5> ships_ptr_arr = {destroyer, submarine, cruiser, battleship, carrier};

    static SDLGui::GridWidget& grid = SDLGui::Grid("preparation_grid");

    static std::pair<uint32_t, uint32_t> grid_cell_coords;
    static SDL_FRect grid_hover_cell_data;
    static std::pair<float, float> image_position;


    // Because we should code DRY
    for(int i = 0; i < 5; i++){
        if(ships_widget_arr[i]->isGrabbed()){
            if(grid.isHovered()){
                grid_cell_coords = grid.getHoverIndices();
                grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
                ships_widget_arr[i]->resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
            }
        }

        // ATTENTION -> I think SDL and cpp are handling x y differently, so I'm swapping them here
        // Okey, sometimes, it just isn't working correctly when checking but I'm too tired to check why
        if(ships_widget_arr[i]->onDrop()){
            if(!grid.isHovered()) ships_widget_arr[i]->reset();
            else{
                image_position = ships_widget_arr[i]->getPosition();
                grid_cell_coords = grid.getHoverIndices();
                ships_ptr_arr[i]->set_is_horizontal(!ships_widget_arr[i]->isRotated());
                bool can_be_placed = 
                    own_board.is_valid_placement(grid_cell_coords.first, grid_cell_coords.second, *ships_ptr_arr[i]);
                if(can_be_placed){
                    grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
                    ships_widget_arr[i]->resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
                    own_board.place_ship(grid_cell_coords.first, grid_cell_coords.second, ships_ptr_arr[i]->get_name());
                }
                else{
                    ships_widget_arr[i]->reset();
                }
            }
        }
    }


    if (SDLGui::TextButton("ready_button")) {
        SDLGui::TextButton("ready_button").disable();
        Player* player = game_state_->get_players()[0];
        if(own_board.is_valid_configuration()){
            ClientNetworkManager::send_message(PreparedRequest(game_state_->get_id(), player->get_id(), own_board.get_ship_configuration()).to_string());
        }
        else{
            own_board.reset_board();
            for(int i = 0; i < 5; i++){
                ships_widget_arr[i]->reset();
            }
        }
    }


    if(SDLGui::TextButton("helpButton")){
        if(help_button_counter_ == 0){
            ++help_button_counter_;
            // Set the background
            SDLGui::Text("helpMessageText").updateText(512, "Press R while holding a ship to rotate it. Click on the help button to close this message.");
        }
        else{
            --help_button_counter_;
            // Set the background to nothing
            SDLGui::Text("helpMessageText").updateText(512, "");
        }
    }

    if(game_state_->get_players()[1]->get_is_prepared()){
        SDLGui::Text("enemy_prepared_text").updateText(32, "Second player is prepared!");
    }

    SDLGui::end();
}