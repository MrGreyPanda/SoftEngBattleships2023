#include "end_panel.h"

GameState* EndPanel::game_state_ = nullptr;

void EndPanel::init(){
    SDLGui::SDLGuiContext* end_panel_context =
    new SDLGui::SDLGuiContext("end_window");

    SDLGui::TextWidget* winner_or_loser_text = new SDLGui::TextWidget(
    "winner_or_loser_text", "", .06f, .1f, .4f, .09f, 0.,
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

    SDLGui::GridWidget* end_enemy_board = 
        new SDLGui::GridWidget("end_enemy_board", .55f, .05f, .4f, .8f,
        0., 10, 10, SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    end_panel_context->addWidget(end_enemy_board);


    EnemyBoard enemy_board = game_state_->get_players()[0]->get_enemy_board();
    unsigned short grid_size = game_state_->get_players()[0]->get_enemy_board().get_grid_size();
    for(int i = 0; i < grid_size; i++){
        for(int j = 0; j < grid_size; j++){
            unsigned short grid_value = enemy_board.get_grid_value(i, j);
            bool was_shot = enemy_board.get_is_shot(i, j);
            if(grid_value > 0 && grid_value < 6){
                if(was_shot){
                    // Here, change color
                }
                else{
                    // Here, change color
                }
            }
        }
    }

    SDLGui::SDLGuiEnvironment::pushContext(end_panel_context);

}

void EndPanel::render() {
    SDLGui::begin("end_window");


    if(game_state_->get_players()[0]->has_won){
        SDLGui::Text("winner_or_loser_text").updateText(64, "You Won!");
    }
    else{
        SDLGui::Text("winner_or_loser_text").updateText(64, "You Lost!");
    }

    if(SDLGui::TextButton("end_play_again_button")){
        // Need to redesign this
        game_state_->reset_state();
        ClientNetworkManager::send_message(JoinRequest().to_string());
    }
    SDLGui::end();
}