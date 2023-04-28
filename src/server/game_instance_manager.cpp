// Adapted from LAMA example project

#include "game_instance_manager.h"

#include "player_manager.h"
#include "server_network_manager.h"

// Initialize static map
std::unordered_map<std::string, GameInstance *> GameInstanceManager::games_lut;

GameInstance *GameInstanceManager::create_new_game() {
    GameInstance *new_game = new GameInstance();
    games_lut_lock.lock();  // exclusive
    GameInstanceManager::games_lut.insert({new_game->get_id(), new_game});
    games_lut_lock.unlock();
    return new_game;
}

bool GameInstanceManager::get_game_instance(const std::string &game_id,
                                            GameInstance *&game_instance_ptr) {
    game_instance_ptr = nullptr;
    games_lut_lock.lock_shared();
    auto it = GameInstanceManager::games_lut.find(game_id);
    if (it != games_lut.end()) {
        game_instance_ptr = it->second;
    }
    games_lut_lock.unlock_shared();
    return game_instance_ptr != nullptr;
}

bool GameInstanceManager::add_player_to_any_game(
    Player *player, GameInstance *&game_instance_ptr) {
    // check that player is not already subscribed to another game
    if (game_instance_ptr != nullptr) {
        GameInstance *player_game_ptr =
            _find_game_by_player_id(player->get_id());
        std::string player_game_id = player_game_ptr->get_id();

        if (player_game_ptr != nullptr &&
            player_game_id != game_instance_ptr->get_id()) {
            throw std::runtime_error(
                "Could not join game with id " + game_instance_ptr->get_id() +
                ". Player is already active in a different game with id " +
                player_game_id);
        } else {
            throw std::runtime_error(
                "Could not join game. Player is already active in a game");
        }
        // TODO add a possibility to not throw an error if the player
        // has already joined the same game maybe?
        // otherwise this check can be greatly simplified
    } else {
        // Join any non-full, non-started game
        // make at most 10 attempts of joining a src (due to concurrency,
        // the game could already be full or started by the time
        // try_add_player_to_any_game() is invoked) But with only few
        // concurrent requests it should succeed in the first iteration.
        game_instance_ptr = _find_joinable_game_instance();
        if (try_add_player(player, game_instance_ptr)) {
            return true;
        }
    }
    return false;
}

bool GameInstanceManager::try_add_player(Player *player,
                                         GameInstance *&game_instance_ptr) {
    if (game_instance_ptr != nullptr) {
        return game_instance_ptr->add_player(player);
    }
    return false;
}

bool GameInstanceManager::try_remove_player(Player *player,
                                            const std::string &game_id) {
    GameInstance *game_instance_ptr = nullptr;
    if (get_game_instance(game_id, game_instance_ptr)) {
        return try_remove_player(player, game_instance_ptr);
    } else {
        throw std::runtime_error(
            "The requested src could not be found. Requested src id was " +
            game_id);
        return false;
    }
}

bool GameInstanceManager::try_remove_player(Player *player,
                                            GameInstance *&game_instance_ptr) {
    return game_instance_ptr->remove_player(player);
}

GameInstance *GameInstanceManager::_find_game_by_player_id(
    const std::string &player_id) {
    GameInstance *game_instance_ptr = nullptr;
    games_lut_lock.lock_shared();
    for (auto it = games_lut.begin(); it != games_lut.end(); ++it) {
        if (it->second->has_player(player_id)) {
            game_instance_ptr = it->second;
            break;
        }
    }
    games_lut_lock.unlock_shared();
    return game_instance_ptr;
}