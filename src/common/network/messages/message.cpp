#include "message.h"

std::string Message::get_game_id() const { return game_id_; }

std::string Message::get_player_id() const { return player_id_; }

json Message::to_json() const {
    json j         = BaseMessage::to_json();
    j["game_id"]   = game_id_;
    j["player_id"] = player_id_;
    return j;
}