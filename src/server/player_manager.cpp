// Adapted from LAMA example project

#include "player_manager.h"

// Initialize static map
std::unordered_map<std::string, Player*> PlayerManager::players = {};

bool PlayerManager::try_get_player(const std::string& player_id, Player *&player_ptr) {
    player_ptr = nullptr;
    rw_lock.lock_shared();
    auto it = PlayerManager::players.find(player_id);
    if (it != players.end()) {
        player_ptr = it->second;
    }
    rw_lock.unlock_shared();
    return player_ptr;
}

bool PlayerManager::add_or_get_player(const std::string& player_id, Player *&player_ptr) {
    if (try_get_player(player_id, player_ptr)) {
        return true;
    }
    player_ptr = new Player(player_id);
    rw_lock.lock();    // exclusive
    PlayerManager::players.insert({player_id, player_ptr});
    rw_lock.unlock();
    return true;
}

bool PlayerManager::remove_player(const std::string& player_id, Player *&player) {
    if (try_get_player(player_id, player)) {
        rw_lock.lock();    // exclusive
        PlayerManager::players.erase(player_id);
        rw_lock.unlock();
        return true;
    }
    return false;
}

