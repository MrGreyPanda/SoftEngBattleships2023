#include "shoot_response.h"

ShootResponse::ShootResponse(const json& data)
    : Response(data), ShootRequest(data) {}

ShootResponse::ShootResponse(const std::string& game_id,
                             const std::string& player_id, unsigned short x,
                             unsigned short y)
    : Response(MessageType::ShootResponseType, game_id, player_id),
      ShootRequest(game_id, player_id, x, y) {}

ShootResponse::ShootResponse(const std::string& game_id,
                             const std::string& player_id, unsigned short x,
                             unsigned short y, const std::string& error)
    : Response(MessageType::ShootResponseType, game_id, player_id, error),
      ShootRequest(game_id, player_id, x, y) {}

json ShootResponse::to_json() const {
    json j = Response::to_json();
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
