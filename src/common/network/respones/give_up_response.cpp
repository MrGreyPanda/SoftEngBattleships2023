#include "give_up_response.h"

GiveUpResponse::GiveUpResponse(const json& data) : Response(data) {}

GiveUpResponse::GiveUpResponse(const std::string& game_id,
                               const std::string& player_id)
    : Response(MessageType::GiveUpResponseType, game_id, player_id) {}
