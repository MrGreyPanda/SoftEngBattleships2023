#include "prepared_response.h"

PreparedResponse::PreparedResponse(const json& data)
    : Response(data), PreparedRequest(data) {}

PreparedResponse::PreparedResponse(const std::string& game_id,
                                   const std::string& player_id,
                                   const std::vector<Ship>& ships)
    : PreparedRequest(game_id, player_id, ships),
      Response(MessageType::PreparedResponseType, game_id, player_id) {}

PreparedResponse::PreparedResponse(const std::string& game_id,
                                   const std::string& player_id,
                                   const std::vector<Ship>& ships,
                                   const std::string& error)
    : Response(MessageType::PreparedResponseType, game_id, player_id, error),
      PreparedRequest(game_id, player_id, ships) {}

PreparedResponse::PreparedResponse(const std::string& game_id,
                                   const std::string& player_id,
                                   const std::vector<ShipData>& ship_data)
    : Response(MessageType::PreparedResponseType, game_id, player_id),
      PreparedRequest(game_id, player_id, ship_data) {}

PreparedResponse::PreparedResponse(const std::string& game_id,
                                   const std::string& player_id,
                                   const std::vector<ShipData>& ship_data,
                                   const std::string& error)
    : Response(MessageType::PreparedResponseType, game_id, player_id, error),
      PreparedRequest(game_id, player_id, ship_data) {}

json PreparedResponse::to_json() const {
    json j = PreparedRequest::to_json();
    j.merge_patch(Response::to_json());

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

bool PreparedResponse::is_valid() const {
    return Response::get_error().empty();
}