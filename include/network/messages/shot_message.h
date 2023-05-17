#pragma once

#include "shoot_request.h"

class ShotMessage : public ShootRequest {
   public:
    ShotMessage(const json& data);
    ShotMessage(const std::string& game_id, const std::string& player_id,
                const unsigned short& x, const unsigned short& y, bool has_hit);

    bool has_hit() const;
   private:
    bool has_hit_;
};
