#pragma once

#include "response.h"

class GiveUpResponse : public Response {
   public:
    GiveUpResponse(const json& data);
    GiveUpResponse(const std::string& game_id, const std::string& player_id);
};
