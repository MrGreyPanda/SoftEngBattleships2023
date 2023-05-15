#include "join_response.h"

JoinResponse::JoinResponse() : Response(MessageType::JoinResponseType) {}

JoinResponse::JoinResponse(const json& data) : Response(data) {}

JoinResponse::JoinResponse(const std::string& game_id,
                           const std::string& player_id)
    : Response(MessageType::JoinResponseType, game_id, player_id) {}

JoinResponse::JoinResponse(const std::string& game_id,
                           const std::string& player_id,
                           const std::string& error)
    : Response(MessageType::JoinResponseType, game_id, player_id, error) {}