#include "game_controller.h"

GameState GameController::game_state_ = GameState();

std::vector<bool> GameController::InitializedPannels_ = {true, false, false,
                                                         false, false};

void GameController::init() {
    SDLGui::init("Battleships", SDL_WINDOWPOS_UNDEFINED,
                 SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_RESIZABLE,
                 SDL_RENDERER_ACCELERATED);
    assert(SDLGui::isInitialized() && "SDLGui is not initialized");

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

    ClientResponseMessageHandler::set_game_controller_game_state(&game_state_);
}


void GameController::run() {
    GameController::render();
    SDLGui::quit();
}

void GameController::render() {
    SDLGui::start();
    while (SDLGui::isRunning()) {
        SDLGui::newFrame();

        switch (game_state_.get_phase()) {
            case Connection:
                ConnectionPanel::render();
                break;
            case Lobby:
                LobbyPanel::render();
                break;
            case Preparation:
                PreparationPanel::render();
                break;
            case Battle:
                BattlePanel::render();
                break;
            case End:
                EndPanel::render();
                break;
        }

        SDLGui::renderFrame();
    }
}

void GameController::disconnect_from_server() {
    if (ClientNetworkManager::disconnect()) {
        game_state_.reset_state();
        game_state_.set_phase(Connection);
    } else {
        // Could not disconnect
        std::cout << "Could not disconnect" << std::endl;
    }
}