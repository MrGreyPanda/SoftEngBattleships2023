#include "game_controller.h"

void GameController::init() {
    SDLGui::init("Battleships", SDL_WINDOWPOS_UNDEFINED,
                 SDL_WINDOWPOS_UNDEFINED, 1080, 720,
                 0,  // SDL_WINDOW_RESIZABLE
                 SDL_RENDERER_ACCELERATED);
    assert(SDLGui::SDLGuiCore::isInitialized() && "SDLGui is not initialized");

    ConnectionWindow::init();
}

void GameController::run() {
    GameController::render();
    SDLGui::quit();
}

void GameController::render() {
    SDLGui::start();
    while (SDLGui::isRunning()) {
        SDLGui::newFrame();

        ConnectionWindow::render();

        SDLGui::renderFrame();
    }
}