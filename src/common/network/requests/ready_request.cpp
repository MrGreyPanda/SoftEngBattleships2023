#include "ready_request.h"

ReadyRequest::ReadyRequest(std::string game_id, std::string player_id)
    : Message(MessageType::ReadyRequestType, game_id, player_id) {}

ReadyRequest::ReadyRequest(const json& data) : Message(data) {}