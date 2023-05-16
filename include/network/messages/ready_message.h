#pragma once

#include "message.h"

class ReadyMessage : public Message {
   public:
    ReadyMessage(const json& data);
    ReadyMessage(const std::string& game_id, const std::string& player_id);
};
