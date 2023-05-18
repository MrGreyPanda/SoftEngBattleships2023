#include "shot_message.h"

ShotMessage::ShotMessage(const json& data) : ShootRequest(data) {
    has_hit_            = data.at("has_hit").get<bool>();
    has_destroyed_ship_ = data.at("has_destroyed_ship").get<bool>();
    destroyed_ship_     = data.at("destroyed_ship").get<ShipData>();
}

ShotMessage::ShotMessage(const std::string& game_id,
                         const std::string& player_id, const unsigned short& x,
                         const unsigned short& y, bool has_hit)
    : ShootRequest(game_id, player_id, x, y),
      has_hit_(has_hit),
      has_destroyed_ship_(false) {}

ShotMessage::ShotMessage(const std::string& game_id,
                         const std::string& player_id, const unsigned short& x,
                         const unsigned short& y,
                         const ShipData& destroyed_ship)
    : ShootRequest(game_id, player_id, x, y),
      has_hit_(true),
      has_destroyed_ship_(true),
      destroyed_ship_(destroyed_ship) {}

bool ShotMessage::has_hit() const { return has_hit_; }

MessageType ShotMessage::get_type() const {
    return MessageType::ShotMessageType;
}

json ShotMessage::to_json() const {
    json data                  = ShootRequest::to_json();
    data["has_hit"]            = has_hit_;
    data["has_destroyed_ship"] = has_destroyed_ship_;
    data["destroyed_ship"]     = destroyed_ship_;
    return data;
}

bool ShotMessage::has_destroyed_ship() const { return has_destroyed_ship_; }

ShipData ShotMessage::get_destroyed_ship() const { return destroyed_ship_; }
