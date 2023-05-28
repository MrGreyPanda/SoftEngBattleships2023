#pragma once

#include "response.h"

/**
 * @brief Response sent from the server to a client as a response to a
 * GiveUpRequest
 */
class GiveUpResponse : public Response {
   public:
    GiveUpResponse(const json& data);
    GiveUpResponse(const std::string& game_id, const std::string& player_id);
};
