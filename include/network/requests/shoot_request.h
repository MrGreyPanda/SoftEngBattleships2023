#pragma once

#include "message.h"

/**
 * @brief A message sent from the client to the server when the player wants to
 * shoot at their opponent.
 */
class ShootRequest : public Message {
   public:
    ShootRequest(const json& data);
    ShootRequest(std::string game_id, std::string player_id, unsigned short x,
                 unsigned short y);

    unsigned short get_x() const;
    unsigned short get_y() const;

    json to_json() const override;

   private:
    unsigned short x_;
    unsigned short y_;
};
