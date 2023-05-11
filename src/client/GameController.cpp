#include "GameController.h"

void GameController::init()
{
    SDLGui::init("Battleships", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_RESIZABLE, SDL_RENDERER_ACCELERATED);
    assert(SDLGui::SDLGuiCore::isInitialized() && "SDLGui is not initialized");

    //SDLGui::SDLGuiContext* testContext = new SDLGui::SDLGuiContext("testContext");

    //SDLGui::TextButtonWidget* testButton = new SDLGui::TextButtonWidget("testButton", "Test", .1f, .2f, .1f, .1f, 0., SDLGui::TextButtonFlagsExt_CenterText | SDLGui::TextButtonFlagsExt_CenterHorizontal);
    //testContext->addWidget(testButton);

    //SDLGui::SDLGuiEnvironment::pushContext(testContext);

    ConnectionWindow::init();
}

void GameController::run()
{
    GameController::render();
    SDLGui::quit();
}

void GameController::render()
{
    SDLGui::start();
    while (SDLGui::isRunning()) {
        SDLGui::newFrame();

        //SDLGui::begin("testContext");

        //if (SDLGui::TextButton("testButton")) printf("Test button pressed\n");

        //SDLGui::end();

        ConnectionWindow::render();

        SDLGui::renderFrame();
    }
}