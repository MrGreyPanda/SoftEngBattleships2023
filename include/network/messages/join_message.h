#pragma once

#include "message.h"

class JoinMessage : public Message {
   public:
    JoinMessage(const json& data);
    JoinMessage(const std::string& game_id, const std::string& player_id);
};
