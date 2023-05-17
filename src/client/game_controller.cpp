#include "game_controller.h"

GameState GameController::game_state_ = GameState();
std::string GameController::game_player_id_;

void GameController::init() {
    SDLGui::init("Battleships", SDL_WINDOWPOS_UNDEFINED,
                 SDL_WINDOWPOS_UNDEFINED, 1080, 720,
                 SDL_WINDOW_RESIZABLE,
                 SDL_RENDERER_ACCELERATED);
    assert(SDLGui::SDLGuiCore::isInitialized() && "SDLGui is not initialized");

    ConnectionPanel::set_game_state(&game_state_);
    ConnectionPanel::init();

    LobbyPanel::set_game_state(&game_state_);
    LobbyPanel::init();

    PreparationPanel::set_game_state(&game_state_);
    PreparationPanel::init();

    BattlePanel::set_game_state(&game_state_);
    BattlePanel::init();

    EndPanel::set_game_state(&game_state_);
    EndPanel::init();

    // game_state_.set_phase(Battle);
}

void GameController::set_player_id(std::string player_id) {
    game_player_id_ = player_id;
}

std::string GameController::get_player_id() {
    return game_player_id_;
}

void GameController::run() {
    GameController::render();
    SDLGui::quit();
}

void GameController::render() {
    SDLGui::start();
    while (SDLGui::isRunning()) {
        SDLGui::newFrame();

        if(game_state_.get_phase() == End) EndPanel::render();
        if(game_state_.get_phase() == Battle) BattlePanel::render();
        if (game_state_.get_phase() == Preparation) PreparationPanel::render();
        if (game_state_.get_phase() == Lobby) LobbyPanel::render();
        if (game_state_.get_phase() == Connect) ConnectionPanel::render();

        SDLGui::renderFrame();
    }
}