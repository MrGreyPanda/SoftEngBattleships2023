#include "shoot_response.h"

ShootResponse::ShootResponse(const json& data)
    : Response(data), ShotMessage(data) {
    is_valid_ = data.at("is_valid").get<bool>();
}

ShootResponse::ShootResponse(const std::string& game_id,
                             const std::string& player_id,
                             const unsigned short& x, const unsigned short& y,
                             const bool& is_valid, const std::string& error)
    : Response(MessageType::ShootResponseType, game_id, player_id, error),
      ShotMessage(game_id, player_id, x, y, false),
      is_valid_(is_valid) {}

ShootResponse::ShootResponse(const std::string& game_id,
                             const std::string& player_id,
                             const unsigned short& x, const unsigned short& y,
                             const bool& has_hit)
    : Response(MessageType::ShootResponseType, game_id, player_id),
      ShotMessage(game_id, player_id, x, y, has_hit),
      is_valid_(true) {}

ShootResponse::ShootResponse(const std::string& game_id,
                             const std::string& player_id,
                             const unsigned short& x, const unsigned short& y,
                             const ShipData& destroyed_ship_)
    : Response(MessageType::ShootResponseType, game_id, player_id),
      ShotMessage(game_id, player_id, x, y, destroyed_ship_),
      is_valid_(true) {}

json ShootResponse::to_json() const {
    json j        = Response::to_json();
    j["is_valid"] = is_valid_;
    j.merge_patch(ShotMessage::to_json());
    j["type"] = "shoot_response";
    return j;
}

std::string ShootResponse::to_string() const { return to_json().dump(); }

std::string ShootResponse::get_game_id() const {
    return ShotMessage::get_game_id();
}

std::string ShootResponse::get_player_id() const {
    return ShotMessage::get_player_id();
}

bool ShootResponse::is_valid() const { return is_valid_; }

MessageType ShootResponse::get_type() const {
    return MessageType::ShootResponseType;
}