#pragma once

#include "message.h"

class PreparedMessage : public Message {
   public:
    PreparedMessage(const json& data);
    PreparedMessage(const std::string& game_id, const std::string& player_id);

};