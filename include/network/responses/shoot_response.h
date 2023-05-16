#pragma once

#include "response.h"
#include "shoot_request.h"

class ShootResponse : public ShootRequest, Response {
   public:
    ShootResponse(const json& data);
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  unsigned short x, unsigned short y);
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  unsigned short x, unsigned short y,
                  const std::string& error);

    json to_json() const;

    std::string to_string() const;

    std::string get_game_id() const;

    std::string get_player_id() const;
};
