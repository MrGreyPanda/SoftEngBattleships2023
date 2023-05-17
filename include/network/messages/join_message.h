#pragma once

#include "message.h"

class JoinedMessage : public Message {
   public:
    JoinedMessage(const json& data);
    JoinedMessage(const std::string& game_id, const std::string& player_id);
};
