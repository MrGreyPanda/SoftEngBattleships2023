#pragma once

#include "message.h"

class GiveUpRequest : public Message {
   public:
    GiveUpRequest(const json& data);
    GiveUpRequest(const std::string& game_id, const std::string& player_id);
};