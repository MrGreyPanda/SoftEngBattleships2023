#include "shoot_response.h"

ShootResponse::ShootResponse(const json& data)
    : Response(data), ShootRequest(data) {
    is_valid_ = data["is_valid"].get<bool>();
    has_hit_ = data["has_hit"].get<bool>();
    }

ShootResponse::ShootResponse(const std::string& game_id,
                             const std::string& player_id, unsigned short x,
                             unsigned short y, bool is_valid, bool has_hit)
    : Response(MessageType::ShootResponseType, game_id, player_id),
      ShootRequest(game_id, player_id, x, y), is_valid_(is_valid), has_hit_(has_hit){}

ShootResponse::ShootResponse(const std::string& game_id,
                             const std::string& player_id, unsigned short x,
                             unsigned short y, bool is_valid, bool has_hit, const std::string& error)
    : Response(MessageType::ShootResponseType, game_id, player_id, error),
      ShootRequest(game_id, player_id, x, y), is_valid_(is_valid), has_hit_(has_hit) {}

json ShootResponse::to_json() const {
    json j = Response::to_json();
    j["is_valid"] = is_valid_;
    j["has_hit"] = has_hit_;
    j.merge_patch(ShootRequest::to_json());
    return j;
}

std::string ShootResponse::to_string() const { return to_json().dump(); }

std::string ShootResponse::get_game_id() const {
    return ShootRequest::get_game_id();
}

std::string ShootResponse::get_player_id() const {
    return ShootRequest::get_player_id();
}
