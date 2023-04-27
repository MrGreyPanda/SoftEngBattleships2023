// Adapted from LAMA example project

#include "game_instance.h"

#include "server_network_manager.h"
#include "../common/network/responses/full_state_response.h"


GameInstance::GameInstance() {
    _game_state = new GameState();
}

GameState *GameInstance::get_game_state() {
    return _game_state;
}

std::string GameInstance::get_id() {
    return _game_state->get_id();
}

bool GameInstance::is_player_allowed_to_play(Player *player) {
    return _game_state->is_allowed_to_play_now(player);
}

bool GameInstance::has_started() {
    return _game_state->has_started();
}

bool GameInstance::has_finished() {
    return _game_state->has_finished();
}

bool GameInstance::start_game() {

}

bool GameInstance::remove_player(Player *player) {

}

bool GameInstance::add_player(Player *new_player) {

}

bool GameInstance::shoot() {

}

bool GameInstance::player_prepared() {

}

