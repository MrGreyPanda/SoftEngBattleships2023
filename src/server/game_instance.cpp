// Adapted from LAMA example project

#include "game_instance.h"

GameInstance::GameInstance() : _game_state(new GameState()), _players() {}

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
    return true;  // TODO, do we need an error check here for set_phase?
}

bool GameInstance::remove_player(Player *player) {
    _lock.lock();
    if (_players[0] == player) {
        _players[0] = nullptr;
        delete player;
        _lock.unlock();
        return true;
    } else if (_players[1] == player) {
        _players[1] = nullptr;
        delete player;
        _lock.unlock();
        return true;
    }
    _lock.unlock();
    return false;
}

bool GameInstance::add_player(Player *new_player) {
    _lock.lock();
    if (_players[0] == nullptr) {
        _players[0] = new_player;
        _lock.unlock();
        return true;
    } else if (_players[1] == nullptr) {
        _players[1] = new_player;
        _lock.unlock();
        return true;
    }
    _lock.unlock();
    return false;
}

bool GameInstance::shoot() {
    // TODO
    throw std::runtime_error("Not implemented");
}

bool GameInstance::player_prepared() {
    // TODO
    throw std::runtime_error("Not implemented");
}

bool GameInstance::has_player(std::string player_id) {
    // TODO
    throw std::runtime_error("Not implemented");
}

bool GameInstance::is_full() {
    _lock.lock();
    if (_players[0] == nullptr || _players[1] == nullptr) {
        _lock.unlock();
        return false;
    }
    _lock.unlock();
    return true;
}
