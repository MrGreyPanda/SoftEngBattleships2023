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

bool GameInstance::start_preparation() {
    return game_state_->start_preparation();
}

bool GameInstance::start_battle() { return game_state_->start_battle(); }

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

void GameInstance::handle_shot(const std::string &player_id,
                               std::string &other_player_id,
                               const unsigned short x, const unsigned short y,
                               bool &is_valid, bool &has_hit,
                               bool &has_destroyed_ship,
                               ShipData &destroyed_ship, bool &has_won_game) {
    // set all the referenced values
    other_player_id    = "";
    is_valid           = false;
    has_hit            = false;
    has_destroyed_ship = false;
    destroyed_ship     = ShipData();
    has_won_game       = false;

    // 0. check if the game has started and it's this players turn!
    // 1. check if other player own board was already shot at this position
    // 2. check if this players enemy board was already shot at this position
    // 3. Place a shot on both boards
    // 4. Check if the shot hit a ship
    // 5. Check if the shot destroyed a ship
    // 6. If a ship was destroyed, check if the shot decided a game

    // 0. check if the game has started and it's this players turn!
    if (game_state_->get_phase() != Phase::Battle) {
        std::cout
            << "[GameInstance] Error: Battle phase has not started yet\n";
        return;
    }
    if (game_state_->get_turn_player_id() != player_id) {
        std::cout << "[GameInstance] Error: It's not this players turn\n";
        return;
    }

    // 1. check if other player own board was already shot at this position

    // get the other player
    other_player_id = try_get_other_player_id(player_id);
    if (other_player_id.empty()) {
        std::cout << "[GameInstance] Error: Other player id is empty\n";
        return;
    }
    Player *other_player_ptr = game_state_->get_player_by_id(other_player_id);

    if (other_player_ptr == nullptr) {
        std::cout << "[GameInstance] ServerError: Other player ptr is null\n";
        return;
    }

    if (other_player_ptr->get_own_board().get_is_shot(x, y)) {
        return;
    }

    Player *player_ptr = game_state_->get_player_by_id(player_id);
    if (player_ptr == nullptr) {
        std::cout << "[GameInstance] Server Error: Player ptr is null\n";
        return;
    }

    // 2. check if this players enemy board was already shot at this position
    if (player_ptr->get_enemy_board().get_is_shot(x, y)) {
        return;
    }

    // 3. Place a shot on both boards
    // this is a valid shot, set the is_shot value to true
    is_valid = true;
    std::cout << "[GameInstance] (Debug) Shot is valid\n";

    player_ptr->get_enemy_board().set_is_shot(x, y, true);
    other_player_ptr->get_own_board().set_is_shot(x, y, true);

    // 4. Check if the shot hit a ship

    // Check if other players board has a ship at the given coords
    unsigned short grid_value =
        other_player_ptr->get_own_board().get_grid_value(x, y);
    if (grid_value != 0) {
        // Send hit message to client
        has_hit = true;

        Ship *ship_ptr = other_player_ptr->get_own_board().get_ship(x, y);

        // Update the ships health
        other_player_ptr->get_own_board().update_ship(x, y);

        // 5. Check if the shot destroyed a ship
        if (ship_ptr->get_is_sunk()) {
            // Send ship destroyed message to client that shot
            has_destroyed_ship = true;
            destroyed_ship     = ship_ptr->get_data();
            std::cout << "[GameInstance] (Debug) Ship destroyed\n";

            // 6. If a ship was destroyed, check if the shot decided a game
            if (other_player_ptr->has_lost()) {
                std::cout << "[GameInstance] (Debug) Game over\n";
                game_state_->set_phase(End);
                has_won_game = true;
            }
        }
    } else {
        // it was a miss, change turn // TODO
        game_state_->change_turn_player_index();
    }
}

bool GameInstance::set_player_prepared(const std::string &player_id,
                                       const std::array<ShipData, 5> &ships) {
    // 1. Get player by ID
    // 2. Place ships one by one on the board
    // 3. if all ships have valid placements, update the player to be prepared

    // 1. Get player by ID
    Player *player_ptr = game_state_->get_player_by_id(player_id);
    if (player_ptr == nullptr) {
        // The player could not be found
        return false;
    }

    // Debug print ships
    std::cout << "Ships: " << std::endl;
    for (auto ship : ships) {
        std::cout << "Ship: " << ship.name << " " << ship.x << " " << ship.y
                  << " " << ship.is_horizontal << std::endl;
    }

    // 2. Place ships
    bool is_valid_placement =
        player_ptr->get_own_board().set_ship_configuration(ships);
    if (!is_valid_placement) return false;

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
