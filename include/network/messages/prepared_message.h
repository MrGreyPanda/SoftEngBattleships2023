#pragma once

#include "message.h"

/**
 * @brief Message sent to a player when the other player is prepared and ready
 * to battle
 */
class PreparedMessage : public Message {
   public:
    PreparedMessage(const json& data);
    PreparedMessage(const std::string& game_id, const std::string& player_id);
};