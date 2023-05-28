#pragma once

#include "ready_request.h"
#include "response.h"

/**
 * @brief A message sent from the server to the client as a response to a ready
 * request.
 */
class ReadyResponse : public Response {
   public:
    ReadyResponse(const json& data);
    ReadyResponse(const std::string& game_id, const std::string& player_id);
    ReadyResponse(const std::string& game_id, const std::string& player_id,
                  const std::string& error);
};