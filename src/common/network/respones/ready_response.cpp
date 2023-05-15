#include "ready_response.h"

ReadyResponse::ReadyResponse(const json& data) : Response(data) {}

ReadyResponse::ReadyResponse(const std::string& game_id,
                             const std::string& player_id)
    : Response(MessageType::ReadyResponseType, game_id, player_id) {}

ReadyResponse::ReadyResponse(const std::string& game_id,
                             const std::string& player_id,
                             const std::string& error)
    : Response(MessageType::ReadyResponseType, game_id, player_id, error) {}
