#include "battle_panel.h"


GameState* BattlePanel::game_state_ = nullptr;
std::string BattlePanel::game_player_id_;
unsigned short BattlePanel::help_button_counter_ = 0;

void BattlePanel::init()
{
    SDLGui::SDLGuiContext* battle_panel_context = 
        new SDLGui::SDLGuiContext("battlePanelContext");

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
        "turnMessageText", "", .0f, .9f, .3f, .1f, 0.,
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
    

    SDLGui::SDLGuiEnvironment::pushContext(battle_panel_context);
}

void BattlePanel::set_player_id(std::string player_id) { 
    game_player_id_ = player_id; 
}

void BattlePanel::set_game_state(GameState* game_state) {
    game_state_ = game_state; 
}


void BattlePanel::handle_shots(){
    if(SDLGui::GridWidget("enemy_board")){
        std::pair<uint32_t,uint32_t> xy = SDLGui::Grid("enemy_board").getClickIndices();
        short x = (short)xy.first;
        short y = (short)xy.second;
        if(game_state_->get_player_by_id(game_player_id_)->get_enemy_board().is_valid_shot(x, y)){
            // Send a shoot request to the server
            ShootRequest shoot_request(game_state_->get_id(), game_player_id_, x, y);
            ClientNetworkManager::send_message(shoot_request.to_string());
            SDLGui::GridWidget("enemy_board").disable();
        }
    }
}

void BattlePanel::render()
{
    SDLGui::begin("battlePanelContext");
    unsigned short turn = game_state_->get_turn_player_index();
    bool own_turn = game_state_->get_player_id_by_index(turn) == game_player_id_;
    if(own_turn){
        /*if(Grid is enabled)*/
        SDLGui::Text("turnMessageText").updateText(64, "It is your turn.");
        handle_shots();

        /*else if (grid is disabled)*/
        
    }

    else{
        SDLGui::Text("turnMessageText").updateText(64, "It is the enemy' turn.");
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