#include "end_panel.h"

GameState* EndPanel::game_state_ = nullptr;

void EndPanel::init(){
    SDLGui::SDLGuiContext* end_window_context =
    new SDLGui::SDLGuiContext("endWindow");

    SDLGui::TextWidget* winner_or_loser_text = new SDLGui::TextWidget(
    "winner_or_loser_text", "", .06f, .1f, .4f, .09f, 0.,
    SDLGui::TextFlagsExt_CenterTextVertical |
        SDLGui::TextFlagsExt_NoBackground);
    end_window_context->addWidget(winner_or_loser_text);

    SDLGui::TextButtonWidget* diconnect_button = new SDLGui::TextButtonWidget(
    "end_disconnect_button", "Disconnect", 0.1f, .8f, .3f, .08f, 0.,
    SDLGui::TextButtonFlagsExt_CenterText);
    end_window_context->addWidget(diconnect_button);

    SDLGui::TextButtonWidget* play_again_button = new SDLGui::TextButtonWidget(
    "end_play_again_button", "Play Again", 0.6f, .8f, .3f, .08f, 0.,
    SDLGui::TextButtonFlagsExt_CenterText);
    end_window_context->addWidget(play_again_button);

    SDLGui::SDLGuiEnvironment::pushContext(end_window_context);

}

void EndPanel::render() {
    SDLGui::begin("endWindow");

    if(game_state_->get_players()[0]->has_won){
        SDLGui::Text("winner_or_loser_text").updateText(64, "You Won!");
    }
    else{
        SDLGui::Text("winner_or_loser_text").updateText(64, "You Lost!");
    }

    if(SDLGui::TextButton("end_play_again_button")){
        game_state_->reset_state();
        ClientNetworkManager::send_message(JoinRequest().to_string());

    }
    SDLGui::end();
}