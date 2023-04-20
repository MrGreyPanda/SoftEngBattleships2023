// Adapted from LAMA example project

#pragma once

#include <vector>
#include <string>
#include <mutex>

#include "../common/player.h"
#include "../common/gamestate.h"

class GameInstance {

private:
    GameState* _game_state;
    bool is_player_allowed_to_play(Player* player);
    inline static std::mutex modification_lock;

public:
    GameInstance();
    ~GameInstance() {
        if (_game_state != nullptr) {
            delete _game_state;
        }
        _game_state = nullptr;
    }
    std::string get_id();

    GameState* get_game_state();

    bool has_started();
    bool has_ended();

    // game update functions
    bool add_player(Player* new_player);
    bool remove_player(Player* player);
    bool start_game();
    bool shoot();
    bool player_prepared();
};

