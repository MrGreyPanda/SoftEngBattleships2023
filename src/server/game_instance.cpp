// Adapted from LAMA example project

#include "game_instance.h"

#include "server_network_manager.h"
#include "../common/network/responses/full_state_response.h"


GameInstance::GameInstance() {
    game_state = new GameState();
}

GameState *GameInstance::get_game_state() {
    return game_state;
}

std::string GameInstance::get_id() {
    return game_state->get_id();
}

bool GameInstance::has_started() {
    Phase phase = game_state->get_phase();
    return phase == Preparation;
}

bool GameInstance::has_finished() {
    Phase phase = game_state->get_phase();
    return phase == End;
}

bool GameInstance::start_game() {
    Phase phase = Preparation;
    game_state->set_phase(phase);
}

bool GameInstance::remove_player(Player *player) {

}

bool GameInstance::add_player(Player *new_player) {

}

bool GameInstance::shoot() {

}

bool GameInstance::player_prepared() {

}

