#pragma once

#include "message.h"

/**
 * @brief Message sent from a client to the server when the player wants to
 * give up
 */
class GiveUpRequest : public Message {
   public:
    GiveUpRequest(const json& data);
    GiveUpRequest(const std::string& game_id, const std::string& player_id);
};