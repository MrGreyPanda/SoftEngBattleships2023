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
    if (player->get_game_id() != "") {
        if (game_instance_ptr != nullptr &&
            player->get_game_id() != game_instance_ptr->get_id()) {
            throw std::runtime_error(
                "Could not join game with id " + game_instance_ptr->get_id() +
                ". Player is already active in a different game with id " +
                player->get_game_id())
        } else {
            throw std::runtime_error(
                "Could not join game. Player is already active in a game");
        }
        return false;
    }

    if (game_instance_ptr == nullptr) {
        // Join any non-full, non-started game
        for (int i = 0; i < 10; i++) {
            // make at most 10 attempts of joining a src (due to concurrency,
            // the game could already be full or started by the time
            // try_add_player_to_any_game() is invoked) But with only few
            // concurrent requests it should succeed in the first iteration.
            game_instance_ptr = find_joinable_game_instance();
            if (try_add_player(player, game_instance_ptr, err)) {
                return true;
            }
        }
        return false;
    } else {
        return try_add_player(player, game_instance_ptr, err);
    }
}

bool GameInstanceManager::add_player(player *player,
                                     GameInstance *&game_instance_ptr,
                                     std::string &err) {
    if (player->get_game_id() != "") {
        if (player->get_game_id() != game_instance_ptr->get_id()) {
            err = "Player is already active in a different src with id " +
                  player->get_game_id();
        } else {
            err = "Player is already active in this src";
        }
        return false;
    }

    if (game_instance_ptr->add_player(player, err)) {
        player->set_game_id(
            game_instance_ptr
                ->get_id());  // mark that this player is playing in a src
        return true;
    } else {
        return false;
    }
}

bool GameInstanceManager::try_remove_player(player *player,
                                            const std::string &game_id,
                                            std::string &err) {
    GameInstance *game_instance_ptr = nullptr;
    if (try_get_game_instance(game_id, game_instance_ptr)) {
        return try_remove_player(player, game_instance_ptr, err);
    } else {
        err = "The requested src could not be found. Requested src id was " +
              game_id;
        return false;
    }
}

bool GameInstanceManager::try_remove_player(player *player,
                                            GameInstance *&game_instance_ptr,
                                            std::string &err) {
    return game_instance_ptr->try_remove_player(player, err);
}
