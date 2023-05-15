#pragma once

#include "response.h"

class ReadyResponse : public Response {
   public:
    ReadyResponse(const json& data);
    ReadyResponse(const std::string& game_id, const std::string& player_id);
    ReadyResponse(const std::string& game_id, const std::string& player_id,
                  const std::string& error);
};