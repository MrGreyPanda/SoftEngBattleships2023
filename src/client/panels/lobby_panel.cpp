#include "lobby_panel.h"

GameState* LobbyPanel::game_state_ = nullptr;

void LobbyPanel::init() {
    SDLGui::SDLGuiContext* lobby_panel_context =
        new SDLGui::SDLGuiContext("lobby_window");

    SDLGui::ImageWidget* background_image = new SDLGui::ImageWidget(
        "background_image", "../assets/background_img.bmp", -.1f, .0f, 1.3f, 1.f,
        0.,
        SDLGui::ImageFlagsExt_CenterImageVertical |
            SDLGui::ImageFlagsExt_CenterImageHorizontal | SDLGui::ImageFlagsExt_NoBackground);
    lobby_panel_context->addWidget(background_image);

    SDLGui::TextWidget* lobby_phase_title = new SDLGui::TextWidget(
        "lobby_title", "Lobby", 0, .0f, .05f, .6f, .1f, 0.,
        SDLGui::TextFlagsExt_CenterText |
            SDLGui::TextFlagsExt_CenterHorizontal);
    lobby_panel_context->addWidget(lobby_phase_title);

    SDLGui::TextWidget* waiting_text =
        new SDLGui::TextWidget("waiting_text", "Waiting for second player...",
                               0, .06f, .1f, .6f, .06f, 0.,
                               SDLGui::TextFlagsExt_CenterVertical |
                                   SDLGui::TextFlagsExt_CenterHorizontal |
                                   SDLGui::TextFlagsExt_NoBackground |
                                   SDLGui::TextFlagsExt_CenterText);
    lobby_panel_context->addWidget(waiting_text);

    SDLGui::TextButtonWidget* battle_button = new SDLGui::TextButtonWidget(
        "battle_button", "Battle", 0.f, .88f, .4f, .08f, 0.f,
        SDLGui::TextButtonFlagsExt_CenterHorizontal |
            SDLGui::TextButtonFlagsExt_CenterText);
    lobby_panel_context->addWidget(battle_button);
    battle_button->disable();

    SDLGui::TextButtonWidget* disconnect_button = new SDLGui::TextButtonWidget(
        "disconnect_button", "Disconnect", 0.05f, .05f, .1f, .05f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText);
    lobby_panel_context->addWidget(disconnect_button);

    SDLGui::pushContext(lobby_panel_context);
}

void LobbyPanel::render() {
    SDLGui::begin("lobby_window");

    if (check_is_full()) {
        SDLGui::TextButton("battle_button").enable();
        SDLGui::Text("waiting_text")
            .updateText(32, 0, "Second player joined!");
        if (game_state_->get_players()[1]->get_is_ready()) {
            SDLGui::Text("waiting_text")
                .updateText(32, 0, "Second player is ready!");
        } else {
            SDLGui::Text("waiting_text")
                .updateText(32, 0, "Second player joined!");
        }
    } else {
        SDLGui::Text("waiting_text")
            .updateText(32, 0, "Waiting for second player...");
    }

    if (SDLGui::TextButton("battle_button")) {
        ClientNetworkManager::send_message(
            ReadyRequest(game_state_->get_id(),
                         game_state_->get_players()[0]->get_id())
                .to_string());
    }

    if (game_state_->get_players()[0]->get_is_ready())
        SDLGui::TextButton("battle_button").disable();

    if (game_state_->all_players_ready()) game_state_->set_phase(Preparation);

    if (SDLGui::TextButton("disconnect_button")) {
        if (ClientNetworkManager::disconnect()) {
            game_state_->reset_state();
            game_state_->set_phase(Connection);
        } else {
            // Could not disconnect
            std::cout << "Could not disconnect" << std::endl;
        }
    }

    SDLGui::end();
}

bool LobbyPanel::check_is_full() { return game_state_->is_full(); }
