#include "end_panel.h"

void EndPanel::init(){
    SDLGui::SDLGuiContext* end_window_context =
    new SDLGui::SDLGuiContext("endWindow");

    SDLGui::TextWidget* winner_or_loser_text = new SDLGui::TextWidget(
    "winner_or_loser_text", "You won!", .06f, .1f, .4f, .09f, 0.,
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

}

void EndPanel::render() {
    SDLGui::begin("endWindow");



}