// Adapted from LAMA example project

#include "game_instance.h"

GameInstance::GameInstance() : game_state_(new GameState()) {}

GameState *GameInstance::get_game_state() { return game_state_; }

std::string GameInstance::get_id() const { return game_state_->get_id(); }

bool GameInstance::has_started() const {
    return game_state_->get_phase() == Preparation;
}

bool GameInstance::has_ended() const {
    return game_state_->get_phase() == End;
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

std::string GameInstance::try_get_other_player_id(
    std::string player_id) const {
    lock_.lock();
    std::string other_player_id = game_state_->get_other_player_id(player_id);
    lock_.unlock();
    return other_player_id;
}

bool GameInstance::set_player_ready(std::string player_id) {
    lock_.lock();
    const bool is_success = game_state_->set_player_ready(player_id);
    lock_.unlock();
    return is_success;
}

bool GameInstance::shoot() {
    // TODO
    throw std::runtime_error("Not implemented");
}

bool GameInstance::set_player_prepared(const std::string &player_id,
                                       const std::vector<ShipData> &ships) {
    // 1. Get player by ID
    // 2. Place ships one by one on the board
    // 3. if all ships have valid placements, update the player to be prepared

    // 1. Get player by ID
    Player *player_ptr = game_state_->get_player_by_id(player_id);
    if (player_ptr == nullptr) {
        // The player could not be found
        return false;
    }

    // 2. Place ships one by one on the board
    for (const ShipData &ship_data : ships) {
        Ship *new_ship = new Ship(ship_data);  // FIXME memory leak
        if (!player_ptr->get_own_board().place_ship(ship_data.x, ship_data.y,
                                                    *new_ship)) {
            // The ship could not be placed
            return false;
        }
    }
    // all ships have been placed successfully, the configuration is valid

    // 3. update the player to be prepared
    player_ptr->set_prepared();

    return true;
}

bool GameInstance::has_player(std::string player_id) const {
    lock_.lock();
    for (Player *player_ptr : game_state_->get_players()) {
        if (player_ptr->get_id() == player_id) {
            lock_.unlock();
            return true;
        }
    }
    lock_.unlock();
    return false;
}

bool GameInstance::is_full() const { return game_state_->is_full(); }

bool GameInstance::all_players_ready() const {
    return game_state_->all_players_ready();
}

bool GameInstance::all_players_prepared() const {
    return game_state_->all_players_prepared();
}
