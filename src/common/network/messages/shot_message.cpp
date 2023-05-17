#include "shot_message.h"

ShotMessage::ShotMessage(const json& data) : ShootRequest(data) {}

ShotMessage::ShotMessage(const std::string& game_id,
                         const std::string& player_id, const unsigned short& x,
                         const unsigned short& y)
    : ShootRequest(game_id, player_id, x, y) {}
