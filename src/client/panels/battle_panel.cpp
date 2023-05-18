#include "battle_panel.h"


GameState* BattlePanel::game_state_ = nullptr;
unsigned short BattlePanel::help_button_counter_ = 0;
Player* BattlePanel::player_ = nullptr;

void BattlePanel::init()
{
    static SDL_FRect grid_hover_cell_data;

    set_player_ptr(game_state_->get_players()[0]);
    OwnBoard* players_board = &player_->get_own_board();
    SDLGui::SDLGuiContext* battle_panel_context = 
        new SDLGui::SDLGuiContext("battle_panel_context");

    SDLGui::GridWidget* own_board = 
        new SDLGui::GridWidget("own_board", .05f, .05f, .4f, .8f,
        0., 10, 10, SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    battle_panel_context->addWidget(own_board);

    SDLGui::GridWidget* enemy_board = 
        new SDLGui::GridWidget("enemy_board", .55f, .05f, .4f, .8f,
        0., 10, 10, SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    battle_panel_context->addWidget(enemy_board);

    SDLGui::TextWidget* battle_phase_title = 
        new SDLGui::TextWidget("battle_title", "Battle Phase",
        .0f, .05f, .6f, .1f, 0., SDLGui::TextFlagsExt_CenterText | 
        SDLGui::TextFlagsExt_CenterHorizontal);
        battle_panel_context->addWidget(battle_phase_title);

    SDLGui::TextWidget* turn_message_text = new SDLGui::TextWidget(
        "turn_message_text", "", .0f, .9f, .3f, .1f, 0.,
        SDLGui::TextFlagsExt_CenterTextHorizontal | SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterHorizontal);
    battle_panel_context->addWidget(turn_message_text);

    SDLGui::TextButtonWidget* resign_button = new SDLGui::TextButtonWidget(
        "resignButton", "Resign", 0.05f, .05f, .1f, .05f, 0.,
         SDLGui::TextButtonFlagsExt_CenterText);
    battle_panel_context->addWidget(resign_button);
    

    SDLGui::TextButtonWidget* help_button = new SDLGui::TextButtonWidget(
        "helpButton", "?", 0.85f, .05f, .1f, .05f, 0.,
         SDLGui::TextButtonFlagsExt_CenterText);
    battle_panel_context->addWidget(help_button);


    SDLGui::TextWidget* help_message_text = new SDLGui::TextWidget(
        "helpMessageText", "", .01f, .1f, .8f, .8f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterHorizontal);
    battle_panel_context->addWidget(help_message_text);

    /**
     * @brief The following widgets are used to display the ships that the player has placed
    */
    SDLGui::DraggableImageWidget* carrier_ship = 
        new SDLGui::DraggableImageWidget("carrier_ship", "../assets/carrier.bmp",
        .6f, .2f, .3f, .12f, 0., 5, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    battle_panel_context->addWidget(carrier_ship);
    // Ship* carrier = players_board->get_ship_by_name(Carrier);
    // grid_hover_cell_data = own_board->getIndexCellCoordinates(carrier->get_x(), carrier->get_y());
    // carrier_ship->resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);

    SDLGui::DraggableImageWidget* battleship_ship = 
        new SDLGui::DraggableImageWidget("battleship_ship", "../assets/battleship.bmp",
        .6f, .35f, .25f, .1f, 0., 4, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    battle_panel_context->addWidget(battleship_ship);

    SDLGui::DraggableImageWidget* cruiser_ship = 
        new SDLGui::DraggableImageWidget("cruiser_ship", "../assets/cruiser.bmp",
        .6f, .5f, .2f, .08f, 0., 3, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    battle_panel_context->addWidget(cruiser_ship);

    SDLGui::DraggableImageWidget* submarine_ship = 
        new SDLGui::DraggableImageWidget("submarine_ship", "../assets/submarine.bmp",
        .6f, .65f, .2f, .08f, 0., 3, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    battle_panel_context->addWidget(submarine_ship);

    SDLGui::DraggableImageWidget* destroyer_ship = 
        new SDLGui::DraggableImageWidget("destroyer_ship", "../assets/destroyer.bmp",
        .6f, .8f, .15f, .06f, 0., 2, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    battle_panel_context->addWidget(destroyer_ship);


    std::array<SDLGui::DraggableImageWidget*, 5> ship_widgets = {
        destroyer_ship, submarine_ship, cruiser_ship, battleship_ship, carrier_ship
    };

    for(int i = 0; i < 5; i ++){
        const Ship* ship = players_board->get_ship_by_index(i);
        grid_hover_cell_data = own_board->getIndexCellCoordinates(ship->get_x(), ship->get_y());
        ship_widgets[i]->resizeToFit(grid_hover_cell_data.x, grid_hover_cell_data.y, grid_hover_cell_data.w, grid_hover_cell_data.h);
        ship_widgets[i]->disable();
    }

    SDLGui::SDLGuiEnvironment::pushContext(battle_panel_context);
}

void BattlePanel::set_game_state(GameState* game_state) {
    game_state_ = game_state; 
}

void BattlePanel::set_player_ptr(Player* player) {
    player_ = player;
}


void BattlePanel::handle_shots(){
    if(SDLGui::GridWidget("enemy_board")){
        std::pair<uint32_t,uint32_t> xy = SDLGui::Grid("enemy_board").getClickIndices();
        short x = (short)xy.first;
        short y = (short)xy.second;
        if(player_->get_enemy_board().is_valid_shot(x, y)){
            // Send a shoot request to the server
            ShootRequest shoot_request(game_state_->get_id(), player_->get_id(), x, y);
            ClientNetworkManager::send_message(shoot_request.to_string());
            player_->has_shot = true;
        }
    }
}

void BattlePanel::render()
{
    SDLGui::begin("battle_panel_context");

    unsigned short grid_size = player_->get_enemy_board().get_grid_size();
    for(int i = 0; i < grid_size; i++){
        for(int j = 0; j < grid_size; j++){
            if(player_->get_enemy_board().get_is_shot(i, j)){
                unsigned short grid_value = player_->get_enemy_board().get_grid_value(i, j);
                if(grid_value == 6){
                    // TODO: set color to red
                }
                else if(grid_value > 0 && grid_value < 6){
                    // TODO: set color to red with brighter opacity, something else
                }
                else if(grid_value == 0){
                    // TODO: set color to blue
                }
                else{
                    // Return error
                }
            }
            if(player_->get_own_board().get_is_shot(i, j)){
                unsigned short grid_value = player_->get_own_board().get_grid_value(i, j);
                if(grid_value > 0 && grid_value < 7){
                    // TODO: set color to red
                }
                else if(grid_value == 0){
                    // TODO: set color to blue
                }
                else{
                    // Return error
                }
            }
        }
    }

    
    if(player_->is_own_turn){
        /*if(Grid is enabled)*/
        if(player_->has_shot){
        }
        else if(!player_->has_shot){
            SDLGui::Text("turn_message_text").updateText(64, "It is your turn.");
            handle_shots();
        }
        
    }

    else{
        SDLGui::Text("turn_message_text").updateText(64, "It is the enemy' turn.");
    }

    if(SDLGui::TextButton("helpButton")){
        if(help_button_counter_ == 0){
            ++help_button_counter_;
            // Set the background
            SDLGui::Text("helpMessageText").updateText(512, "Click on the enemy board to shoot. Click on the resign button to resign. Press R while holding a ship to rotate it. Click on the help button to close this message.");
        }
        else{
            --help_button_counter_;
            // Set the background to nothing
            SDLGui::Text("helpMessageText").updateText(512, "");
        }
    }


    SDLGui::end();
}