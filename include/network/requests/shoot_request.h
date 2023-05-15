#pragma once

#include "message.h"

class ShootRequest : public Message {
   public:
    ShootRequest();
    ShootRequest(const json& data);
    ShootRequest(std::string game_id, std::string player_id, unsigned short x,
                 unsigned short y);

    unsigned short get_x() const;
    unsigned short get_y() const;

    json to_json() const;

   private:
    unsigned short x_;
    unsigned short y_;
};
