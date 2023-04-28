// Adapted from LAMA example project

#include "game_instance.h"

GameInstance::GameInstance() : _game_state(new GameState()) {}

GameState *GameInstance::get_game_state() { return _game_state; }

std::string GameInstance::get_id() { return _game_state->get_id(); }

bool GameInstance::has_started() {
    Phase phase = _game_state->get_phase();
    return phase == Preparation;
}

bool GameInstance::has_ended() {
    Phase phase = _game_state->get_phase();
    return phase == End;
}

bool GameInstance::start_game() {
    Phase phase = Preparation;
    _game_state->set_phase(phase);
}

bool GameInstance::remove_player(Player *player) {
    // TODO
    throw std::runtime_error("Not implemented");
}

bool GameInstance::add_player(Player *new_player) {
    // TODO
    throw std::runtime_error("Not implemented");
}

bool GameInstance::shoot() {
    // TODO
    throw std::runtime_error("Not implemented");
}

bool GameInstance::player_prepared() {
    // TODO
    throw std::runtime_error("Not implemented");
}

bool GameInstance::has_player(std::string player_id) {}
