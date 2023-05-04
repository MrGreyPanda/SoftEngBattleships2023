// Adapted from LAMA example project

#include "player_manager.h"

// Initialize static map
std::unordered_map<std::string, Player> PlayerManager::players_ = {};

bool PlayerManager::try_get_player(const std::string& player_id,
                                   Player* player_ptr) {
    player_ptr = nullptr;
    rw_lock_.lock_shared();
    auto it = PlayerManager::players_.find(player_id);
    if (it != players_.end()) {
        player_ptr = &(it->second);
        rw_lock_.unlock_shared();
        return true;
    }
    rw_lock_.unlock_shared();
    return false;
}

bool PlayerManager::add_or_get_player(const std::string& player_id,
                                      Player* player_ptr) {
    if (try_get_player(player_id, player_ptr)) {
        std::cout << "Player already exists\n";
        return true;
    }
    rw_lock_.lock();  // exclusive
    PlayerManager::players_.insert({player_id, *player_ptr});
    rw_lock_.unlock();
    return false;
}

bool PlayerManager::remove_player(const std::string& player_id,
                                  Player* player) {
    if (try_get_player(player_id, player)) {
        rw_lock_.lock();  // exclusive
        // delete player;
        PlayerManager::players_.erase(player_id);
        rw_lock_.unlock();
        return true;
    }
    return false;
}

PlayerManager::~PlayerManager() { players_.clear(); }