#pragma once

#include "message.h"

/**
 * @brief Message sent to the player when the other player is ready
 */
class ReadyMessage : public Message {
   public:
    ReadyMessage(const json& data);
    ReadyMessage(const std::string& game_id, const std::string& player_id);
};
