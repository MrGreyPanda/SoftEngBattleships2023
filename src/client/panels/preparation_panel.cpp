#include "preparation_panel.h"

GameState* PreparationPanel::game_state_ = nullptr;
unsigned short PreparationPanel::help_button_counter_ = 0;

void PreparationPanel::init()
{
    SDLGui::SDLGuiContext* preparation_panel_context = 
        new SDLGui::SDLGuiContext("preparation_panel_context");

    SDLGui::GridWidget* preparation_grid = 
        new SDLGui::GridWidget("preparation_grid", .05f, .05f, .4f, .8f,
        0., 10, 10, SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    preparation_panel_context->addWidget(preparation_grid);

    SDLGui::TextWidget* preparation_phase_title = 
        new SDLGui::TextWidget("preparation_title", "Preparation Phase",
        .0f, .05f, .6f, .1f, 0., SDLGui::TextFlagsExt_CenterText | 
        SDLGui::TextFlagsExt_CenterHorizontal);
        preparation_panel_context->addWidget(preparation_phase_title);

    SDLGui::TextButtonWidget* ready_button = 
        new SDLGui::TextButtonWidget("ready_button", "Ready", .0f, .9f, .3f, .08f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText | SDLGui::TextButtonFlagsExt_CenterHorizontal);
    preparation_panel_context->addWidget(ready_button);

    SDLGui::DraggableImageWidget* carrier_ship = 
        new SDLGui::DraggableImageWidget("carrier_ship", "../assets/carrier.bmp",
        .6f, .2f, .3f, .12f, 0., 5, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(carrier_ship);
    
    SDLGui::DraggableImageWidget* battleship_ship = 
        new SDLGui::DraggableImageWidget("battleship_ship", "../assets/battleship.bmp",
        .6f, .35f, .3f, .12f, 0., 4, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(battleship_ship);
    
    SDLGui::DraggableImageWidget* cruiser_ship = 
        new SDLGui::DraggableImageWidget("cruiser_ship", "../assets/cruiser.bmp",
        .6f, .5f, .3f, .12f, 0., 3, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(cruiser_ship);
    
    SDLGui::DraggableImageWidget* submarine_ship = 
        new SDLGui::DraggableImageWidget("submarine_ship", "../assets/submarine.bmp",
        .6f, .65f, .3f, .12f, 0., 3, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(submarine_ship);

    SDLGui::DraggableImageWidget* destroyer_ship = 
        new SDLGui::DraggableImageWidget("destroyer_ship", "../assets/destroyer.bmp",
        .6f, .8f, .3f, .12f, 0., 2, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
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

    SDLGui::SDLGuiEnvironment::pushContext(preparation_panel_context);
}

void PreparationPanel::render()
{
    SDLGui::begin("preparation_panel_context");

    static SDLGui::DraggableImageWidget& carrier = SDLGui::DraggableImage("carrier_ship");
    static SDLGui::DraggableImageWidget& battleship = SDLGui::DraggableImage("battleship_ship");
    static SDLGui::DraggableImageWidget& cruiser = SDLGui::DraggableImage("cruiser_ship");
    static SDLGui::DraggableImageWidget& submarine = SDLGui::DraggableImage("submarine_ship");
    static SDLGui::DraggableImageWidget& destroyer = SDLGui::DraggableImage("destroyer_ship");

    static SDLGui::GridWidget& grid = SDLGui::Grid("preparation_grid");

    static std::pair<uint32_t, uint32_t> grid_cell_coords;
    static SDL_FRect grid_hover_cell_data;
    static std::pair<float, float> image_position;

    

    if (carrier.isGrabbed()) {
        if (grid.isHovered()) {
            grid_cell_coords = grid.getHoverIndices();
            grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
            carrier.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
        }
    }
    if (carrier.onDrop()) {
        if (!grid.isHovered()) carrier.reset();
        else {
            image_position = carrier.getPosition();
            grid_cell_coords = grid.getHoverIndices();
            bool can_be_placed = true;  //TO BE SUBSTITUTED BY GRID CHECK FUNCTION
            if (can_be_placed) {
                grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
                carrier.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
            }
            else carrier.reset();
        }
    }

    if (battleship.isGrabbed()) {
        if (grid.isHovered()) {
            grid_cell_coords = grid.getHoverIndices();
            grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
            battleship.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
        }
    }
    if (battleship.onDrop()) {
        if (!grid.isHovered()) battleship.reset();
        else {
            image_position = battleship.getPosition();
            grid_cell_coords = grid.getHoverIndices();
            bool can_be_placed = true;  //TO BE SUBSTITUTED BY GRID CHECK FUNCTION
            if (can_be_placed) {
                grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
                battleship.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
            }
            else battleship.reset();
        }
    }

    if (cruiser.isGrabbed()) {
        if (grid.isHovered()) {
            grid_cell_coords = grid.getHoverIndices();
            grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
            cruiser.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
        }
    }
    if (cruiser.onDrop()) {
        if (!grid.isHovered()) cruiser.reset();
        else {
            image_position = cruiser.getPosition();
            grid_cell_coords = grid.getHoverIndices();
            bool can_be_placed = true;  //TO BE SUBSTITUTED BY GRID CHECK FUNCTION
            if (can_be_placed) {
                grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
                cruiser.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
            }
            else cruiser.reset();
        }
    }

    if (submarine.isGrabbed()) {
        if (grid.isHovered()) {
            grid_cell_coords = grid.getHoverIndices();
            grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
            submarine.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
        }
    }
    if (submarine.onDrop()) {
        if (!grid.isHovered()) submarine.reset();
        else {
            image_position = submarine.getPosition();
            grid_cell_coords = grid.getHoverIndices();
            bool can_be_placed = true;  //TO BE SUBSTITUTED BY GRID CHECK FUNCTION
            if (can_be_placed) {
                grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
                submarine.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
            }
            else submarine.reset();
        }
    }

    if (destroyer.isGrabbed()) {
        if (grid.isHovered()) {
            grid_cell_coords = grid.getHoverIndices();
            grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
            destroyer.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
        }
    }
    if (destroyer.onDrop()) {
        if (!grid.isHovered()) destroyer.reset();
        else {
            image_position = destroyer.getPosition();
            grid_cell_coords = grid.getHoverIndices();
            bool can_be_placed = true;  //TO BE SUBSTITUTED BY GRID CHECK FUNCTION
            if (can_be_placed) {
                grid_hover_cell_data = grid.getIndexCellCoordinates(grid_cell_coords.first, grid_cell_coords.second);
                destroyer.resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
            }
            else destroyer.reset();
        }
    }

    if (SDLGui::TextButton("ready_button")) {
        SDLGui::TextButton("ready_button").disable();
        Player* player = game_state_->get_players()[0];
        //ClientNetworkManager::send_message(PreparedRequest(game_state_->get_id(), player->get_id(), player->get_own_board().get_ship_vec()));
    }
        //game_state_->set_phase(Battle);

    static bool both_players_ready = true;

    for (auto& player : game_state_->get_players()) {
        both_players_ready = both_players_ready && player->get_is_prepared();
    }
    if (both_players_ready) game_state_->set_phase(Battle);

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

    SDLGui::end();
}