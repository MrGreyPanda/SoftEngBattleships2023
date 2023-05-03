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
    if(_game_state->get_phase() == Lobby){
        _game_state->set_phase(phase);
        return true;
    }
    return false; 
}

bool GameInstance::try_remove_player(Player *player) {
    _lock.lock();
    if (_game_state->remove_player(player)){
        _lock.unlock();
        return true;
    }
    _lock.unlock();
    return false;
}

bool GameInstance::try_add_player(Player *new_player) {
    _lock.lock();
    if (_game_state->add_player(new_player)){
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
    _lock.lock();
    for(auto& i : _game_state->get_players()) {
        if (i->get_id() == player_id ){
            _lock.unlock();
            return true;
        }
    }
    _lock.unlock();
    return false;
}
