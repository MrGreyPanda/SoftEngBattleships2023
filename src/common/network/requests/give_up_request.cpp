#include "give_up_request.h"

GiveUpRequest::GiveUpRequest(const json& data) : Message(data) {}

GiveUpRequest::GiveUpRequest(const std::string& game_id,
                             const std::string& player_id)
    : Message(MessageType::GiveUpRequestType, game_id, player_id) {}