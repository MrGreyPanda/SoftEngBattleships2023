#pragma once

#include "response.h"
#include "shot_message.h"

class ShootResponse : public ShotMessage, public Response {
   public:
    ShootResponse(const json& data);
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  unsigned short x, unsigned short y, bool is_valid,
                  bool has_hit);
    ShootResponse(const std::string& game_id, const std::string& player_id,
                  unsigned short x, unsigned short y, bool is_valid,
                  bool has_hit, const std::string& error);

    json to_json() const;

    std::string to_string() const;

    std::string get_game_id() const;

    std::string get_player_id() const;

    bool is_valid() const;

    virtual MessageType get_type() const;

   private:
    bool is_valid_;
};
