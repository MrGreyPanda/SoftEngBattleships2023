#pragma once

#include "response.h"
#include "shoot_request.h"

class ShootResponse : public ShootRequest, Response {
   public:
    ShootResponse(const json& data);
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  unsigned short x, unsigned short y, bool is_valid, bool has_hit);
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  unsigned short x, unsigned short y, bool is_valid, bool has_hit,
                  const std::string& error);

    json to_json() const;

    std::string to_string() const;

    std::string get_game_id() const;

    std::string get_player_id() const;

    bool is_valid() const;

    bool has_hit() const;

    private:
     bool is_valid_;
     bool has_hit_;
};
