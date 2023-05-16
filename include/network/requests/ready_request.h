#pragma once

#include "message.h"

class ReadyRequest : public Message {
   public:
    ReadyRequest(const json& data);
    ReadyRequest(std::string game_id, std::string player_id);
};