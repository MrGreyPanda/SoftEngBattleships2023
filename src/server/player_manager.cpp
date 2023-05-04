// Adapted from LAMA example project

#include "player_manager.h"

// Initialize static map
std::unordered_map<std::string, Player*> PlayerManager::players_ = {};

Player *PlayerManager::try_get_player(const std::string& player_id) {
    rw_lock_.lock_shared();
    auto it = PlayerManager::players_.find(player_id);
    if (it != players_.end()) {
        rw_lock_.unlock_shared();
        return it->second;
    }
    rw_lock_.unlock_shared();
    return nullptr;
}

Player *PlayerManager::add_or_get_player(const std::string& player_id) {
    if (try_get_player(player_id) != nullptr) {
        return try_get_player(player_id);
    }
    Player *player_ptr = new Player(player_id);
    rw_lock_.lock();  // exclusive
    PlayerManager::players_.insert({player_id, player_ptr});
    rw_lock_.unlock();
    return player_ptr;
}

bool PlayerManager::remove_player(const std::string& player_id) {
    if (try_get_player(player_id) != nullptr) {
        rw_lock_.lock();  // exclusive
        // delete player;
        PlayerManager::players_.erase(player_id);
        rw_lock_.unlock();
        return true;
    }
    return false;
}

PlayerManager::~PlayerManager() { 
    for(auto& it : players_) {
        delete it.second;
        it.second = nullptr;
    }
    players_.clear(); 
}