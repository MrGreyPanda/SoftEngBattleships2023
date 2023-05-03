// Adapted from LAMA example project

#include "game_instance.h"

GameInstance::GameInstance() : game_state_(new GameState()) {}

GameState *GameInstance::get_game_state() { return game_state_; }

std::string GameInstance::get_id() { return game_state_->get_id(); }

bool GameInstance::has_started() {
    Phase phase = game_state_->get_phase();
    return phase == Preparation;
}

bool GameInstance::has_ended() {
    Phase phase = game_state_->get_phase();
    return phase == End;
}

bool GameInstance::start_game() {
    Phase phase = Preparation;
    if (game_state_->get_phase() == Lobby) {
        game_state_->set_phase(phase);
        return true;
    }
    return false;
}

bool GameInstance::try_remove_player(Player *player) {
    lock_.lock();
    if (game_state_->remove_player(player)) {
        lock_.unlock();
        return true;
    }
    lock_.unlock();
    return false;
}

bool GameInstance::try_add_player(Player *new_player) {
    lock_.lock();
    if (game_state_->add_player(new_player)) {
        lock_.unlock();
        return true;
    }
    lock_.unlock();
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
    lock_.lock();
    for (auto &i : game_state_->get_players()) {
        if (i->get_id() == player_id) {
            lock_.unlock();
            return true;
        }
    }
    lock_.unlock();
    return false;
}
