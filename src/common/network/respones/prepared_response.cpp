#include "prepared_response.h"

PreparedResponse::PreparedResponse(const json& data)
    : Response(data), PreparedRequest(data) {
    is_valid_ = data.at("is_valid").get<bool>();
}

PreparedResponse::PreparedResponse(const std::string& game_id,
                                   const std::string& player_id,
                                   const std::vector<ShipData>& ship_data,
                                   const bool& is_valid)
    : Response(MessageType::PreparedResponseType, game_id, player_id),
      PreparedRequest(game_id, player_id, ship_data),
      is_valid_(is_valid) {}

PreparedResponse::PreparedResponse(const std::string& game_id,
                                   const std::string& player_id,
                                   const std::vector<ShipData>& ship_data,
                                   const bool& is_valid,
                                   const std::string& error)
    : Response(MessageType::PreparedResponseType, game_id, player_id, error),
      PreparedRequest(game_id, player_id, ship_data),
      is_valid_(is_valid) {}

json PreparedResponse::to_json() const {
    json j = PreparedRequest::to_json();
    j.merge_patch(Response::to_json());
    j["is_valid"] = is_valid_;

    return j;
}

std::string PreparedResponse::to_string() const { return to_json().dump(); }

std::string PreparedResponse::get_game_id() const {
    return PreparedRequest::get_game_id();
}

std::string PreparedResponse::get_player_id() const {
    return PreparedRequest::get_player_id();
}

MessageType PreparedResponse::get_type() const {
    return MessageType::PreparedResponseType;
}

bool PreparedResponse::is_valid() const { return is_valid_; }