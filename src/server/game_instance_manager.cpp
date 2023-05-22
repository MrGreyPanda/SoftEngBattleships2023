// Adapted from LAMA example project

#include "game_instance_manager.h"

#include "player_manager.h"
#include "server_network_manager.h"

// Initialize static map
std::unordered_map<std::string, GameInstance *> GameInstanceManager::games_ =
    {};

GameInstanceManager::~GameInstanceManager() {
    for (auto &it : games_) {
        delete it.second;
        it.second = nullptr;
    }
    games_.clear();
}

GameInstance *GameInstanceManager::create_new_game_() {
    GameInstance *new_game = new GameInstance();
    games_lock_.lock();  // exclusive
    GameInstanceManager::games_.insert({new_game->get_id(), new_game});
    games_lock_.unlock();
    std::cout << "[GameInstanceManager] (Debug) Created new game with ID: "
              << new_game->get_id() << std::endl;
    return new_game;
}

GameInstance *GameInstanceManager::get_game_instance(
    const std::string &game_id) {
    games_lock_.lock_shared();
    auto it = GameInstanceManager::games_.find(game_id);
    if (it != games_.end()) {
        games_lock_.unlock_shared();
        return it->second;
    }
    games_lock_.unlock_shared();
    return nullptr;
}

GameInstance *GameInstanceManager::add_player_to_any_game(Player *player_ptr) {
    // check that player is not already subscribed to another game
    games_lock_.lock();
    // loop over known pairs of game_id and game_instance
    for (auto &it : games_) {
        if (it.second->has_player(player_ptr->get_id())) {
            // this player already is in a game!
            // Return a nullptr to indicate that the player was not 'added' to
            // a game because they were already in one
            games_lock_.unlock();
            return nullptr;
        }
    }

    // again loop over known pairs of game_id and game_instance
    // and try to add the player to a non-full game.
    for (auto &it : games_) {
        if (!it.second->is_full()) {
            if (it.second->try_add_player(player_ptr)) {
                // successfully added player to a game
                games_lock_.unlock();
                return it.second;
            } else {
                // failed to add player to a game
                // this should not happen
                std::cout << "[GameInstanceManager] (Error) Failed to add "
                             "player to a game"
                          << std::endl;
                games_lock_.unlock();
                return nullptr;
            }
        }
    }
    games_lock_.unlock();

    GameInstance *new_game = create_new_game_();
    if (new_game == nullptr) {
        std::cout << "[GameInstanceManager] (Error) Failed to create new game"
                  << std::endl;
        return nullptr;
    }

    const bool added_success = new_game->try_add_player(player_ptr);
    if (!added_success) {
        std::cout << "[GameInstanceManager] (Error) Failed to add player to "
                     "newly created game"
                  << std::endl;
        return nullptr;
    }

    return new_game;
}

bool GameInstanceManager::try_add_player(Player *player_ptr,
                                         GameInstance *&game_instance_ptr) {
    if (game_instance_ptr != nullptr) {
        return game_instance_ptr->try_add_player(player_ptr);
    }
    return false;
}

bool GameInstanceManager::try_remove_player(Player *player_ptr,
                                            GameInstance *&game_instance_ptr) {
    return game_instance_ptr->try_remove_player(player_ptr);
}

bool GameInstanceManager::delete_game_(const std::string &game_id) {
    if(GameInstanceManager::get_game_instance(game_id) != nullptr){
        games_.erase(game_id);
        return true;
    }
    return false;
}

GameInstance *GameInstanceManager::find_game_by_player_id_(
    const std::string &player_id) {
    GameInstance *game_instance_ptr = nullptr;
    games_lock_.lock_shared();
    for (auto it = games_.begin(); it != games_.end(); ++it) {
        if (it->second->has_player(player_id)) {
            game_instance_ptr = it->second;
            break;
        }
    }
    games_lock_.unlock_shared();
    return game_instance_ptr;
}

GameInstance *GameInstanceManager::find_joinable_game_instance_() {
    GameInstance *game_instance_ptr = nullptr;
    games_lock_.lock_shared();
    for (auto it = games_.begin(); it != games_.end(); ++it) {
        if (!it->second->get_game_state()->is_full()) {
            game_instance_ptr = it->second;
            break;
        }
    }
    games_lock_.unlock_shared();
    return game_instance_ptr;
}
