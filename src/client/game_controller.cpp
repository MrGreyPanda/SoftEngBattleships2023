#include "game_controller.h"

GameState GameController::game_state_ = GameState();

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

    // This is for testing purposes only --------
    game_state_.add_player(new Player("1234"));
    if(game_state_.get_players().size() == 1) std::cout << "Player added" << std::endl;
    game_state_.get_players()[0]->is_own_turn = true;
    game_state_.get_players()[0]->has_shot = false;
    unsigned short i = 0;
    for(const auto ship : game_state_.get_players()[0]->get_own_board().get_ship_vec()){
        ship->set_xy(i,i);
        ship->set_is_placed(true);
        i++;
    }
    // -----------------------------------------

    BattlePanel::set_game_state(&game_state_);
    BattlePanel::init();

    EndPanel::set_game_state(&game_state_);
    EndPanel::init();

    ClientResponseMessageHandler::set_game_controller_game_state(&game_state_);
    game_state_.set_phase(Battle);

    printf("All panels initialized\n");
}

void GameController::run() {
    GameController::render();
    SDLGui::quit();
}

void GameController::render() {
    SDLGui::start();
    while (SDLGui::isRunning()) {
        SDLGui::newFrame();

        if (game_state_.get_phase() == End) EndPanel::render();
        if (game_state_.get_phase() == Battle) BattlePanel::render();
        if (game_state_.get_phase() == Preparation) PreparationPanel::render();
        if (game_state_.get_phase() == Lobby) LobbyPanel::render();
        if (game_state_.get_phase() == Connection) ConnectionPanel::render();

        SDLGui::renderFrame();
    }
}