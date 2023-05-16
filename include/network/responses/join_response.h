#pragma once

#include "join_request.h"
#include "response.h"

class JoinResponse : public Response {
   public:
    JoinResponse(const json& data);
    JoinResponse(const std::string& game_id, const std::string& player_id);
    JoinResponse(const std::string& game_id, const std::string& player_id,
                 const std::string& error);
};
