#pragma once

#include "ship.h"
#include "shoot_request.h"

/**
 * @brief Message sent to a player when the other player shot
 */
class ShotMessage : public ShootRequest {
   public:
    ShotMessage(const json& data);

    ShotMessage(const std::string& game_id, const std::string& player_id,
                const unsigned short& x, const unsigned short& y,
                bool has_hit);

    ShotMessage(const std::string& game_id, const std::string& player_id,
                const unsigned short& x, const unsigned short& y,
                const ShipData& destroyed_ship);

    bool has_hit() const;

    virtual json to_json() const override;

    virtual MessageType get_type() const override;

    bool has_destroyed_ship() const;

    ShipData get_destroyed_ship() const;

   private:
    bool has_hit_;
    bool has_destroyed_ship_;
    ShipData destroyed_ship_;
};
