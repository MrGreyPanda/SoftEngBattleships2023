#include "lobby_panel.h"

GameState* LobbyPanel::game_state_ = nullptr;

void LobbyPanel::init() {
    SDLGui::SDLGuiContext* lobbyWindowContext =
        new SDLGui::SDLGuiContext("lobbyWindow");

    SDLGui::TextWidget* waitingText = new SDLGui::TextWidget(
        "waitingText", "Waiting for second player...", .06f, .1f, .4f, .09f, 0.,
        SDLGui::TextFlagsExt_CenterTextVertical |
            SDLGui::TextFlagsExt_CenterText);
    lobbyWindowContext->addWidget(waitingText);

    SDLGui::SDLGuiEnvironment::pushContext(lobbyWindowContext);
}

void LobbyPanel::render() {
    SDLGui::begin("lobbyWindow");
    if(check_is_full()){
        game_state_->set_phase(Phase::Preparation);
    }
    SDLGui::end();
}

bool LobbyPanel::check_is_full() {
    return game_state_->is_full();
}
