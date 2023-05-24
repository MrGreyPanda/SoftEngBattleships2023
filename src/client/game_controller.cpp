#include "game_controller.h"

GameState GameController::game_state_ = GameState();

std::vector<bool> GameController::InitializedPannels_ = {true, false, false, false, false};

void GameController::init() {
    SDLGui::init("Battleships", SDL_WINDOWPOS_UNDEFINED,
                 SDL_WINDOWPOS_UNDEFINED, 1080, 720,
                 SDL_WINDOW_RESIZABLE,
                 SDL_RENDERER_ACCELERATED);
    assert(SDLGui::isInitialized() && "SDLGui is not initialized");

    ConnectionPanel::set_game_state(&game_state_);
    ConnectionPanel::init();

    ClientResponseMessageHandler::set_game_controller_game_state(&game_state_);
    // game_state_.set_phase(End);

    // printf("All panels initialized\n");
}


void GameController::run() {
    GameController::render();
    SDLGui::quit();
}

void GameController::render() {
    SDLGui::start();
    while (SDLGui::isRunning()) {
        SDLGui::newFrame();

        switch(game_state_.get_phase()){
            case Connection:
                ConnectionPanel::render();
                break;
            case Lobby:
                if(InitializedPannels_.at(1) == false){
                    LobbyPanel::set_game_state(&game_state_);
                    LobbyPanel::init();
                    InitializedPannels_.at(1) = true;
                }
                LobbyPanel::render();
                break;
            case Preparation:
                if(InitializedPannels_.at(2) == false){
                    PreparationPanel::set_game_state(&game_state_);
                    PreparationPanel::init();
                    InitializedPannels_.at(2) = true;
                }
                PreparationPanel::render();
                break;
            case Battle:
                if(InitializedPannels_.at(3) == false){
                    BattlePanel::set_game_state(&game_state_);
                    BattlePanel::init();
                    InitializedPannels_.at(3) = true;
                }
                BattlePanel::render();
                break;
            case End:
                if(InitializedPannels_.at(4) == false){
                    EndPanel::set_game_state(&game_state_);
                    EndPanel::init();
                    InitializedPannels_.at(4) = true;
                }
                EndPanel::render();
                break;
        }

        SDLGui::renderFrame();
    }
}