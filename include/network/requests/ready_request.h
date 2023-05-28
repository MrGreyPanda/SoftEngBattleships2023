#pragma once

#include "message.h"

/**
 * @brief A message from the client to the server to indicate that the player
 * in the lobby is ready to play.
 */
class ReadyRequest : public Message {
   public:
    ReadyRequest(const json& data);
    ReadyRequest(std::string game_id, std::string player_id);
};