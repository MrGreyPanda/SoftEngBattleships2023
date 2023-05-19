#include "lobby_panel.h"

GameState* LobbyPanel::game_state_ = nullptr;

void LobbyPanel::init() {
    SDLGui::SDLGuiContext* lobbyWindowContext =
        new SDLGui::SDLGuiContext("lobbyWindow");

    SDLGui::TextWidget* waitingText = new SDLGui::TextWidget(
        "waiting_text", "Waiting for second player...", .06f, .1f, .4f, .09f, 0.,
        SDLGui::TextFlagsExt_CenterTextVertical |
            SDLGui::TextFlagsExt_CenterText);
    lobbyWindowContext->addWidget(waitingText);

    SDLGui::TextButtonWidget* battleButton = new SDLGui::TextButtonWidget(
        "battle_button", "Battle", 0.f, .8f, .4f, .08f, 0.f,
        SDLGui::TextButtonFlagsExt_CenterHorizontal | SDLGui::TextButtonFlagsExt_CenterText
    );
    lobbyWindowContext->addWidget(battleButton);
    battleButton->disable();

    SDLGui::SDLGuiEnvironment::pushContext(lobbyWindowContext);
}

void LobbyPanel::render() {
    SDLGui::begin("lobbyWindow");

    if(check_is_full()){
        SDLGui::TextButton("battle_button").enable();
        SDLGui::Text("waiting_text").updateText(32, "Second player joined!");
    }

    if (SDLGui::TextButton("battle_button")) {
        ClientNetworkManager::send_message(ReadyRequest(
            game_state_->get_id(), 
            game_state_->get_players()[0]->get_id()).to_string());
    }

    if (game_state_->get_players()[0]->get_is_ready())
        SDLGui::TextButton("battle_button").disable();

    if (game_state_->all_players_ready()) 
        game_state_->set_phase(Preparation);

    SDLGui::end();
}

bool LobbyPanel::check_is_full() {
    return game_state_->is_full();
}
