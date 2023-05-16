#pragma once

#include "message.h"
#include "ship.h"

class PreparedRequest : public Message {
   public:
    PreparedRequest(const json& data);
    PreparedRequest(const std::string& game_id, const std::string& player_id,
                    const std::vector<Ship>& ships);
    PreparedRequest(const std::string& game_id, const std::string& player_id,
                    const std::vector<ShipData>& ship_data);

    virtual json to_json() const override;

    const std::vector<Ship>& get_ships() const;
    const std::vector<ShipData>& get_ship_data() const;

   private:
    std::vector<ShipData> ships_;
};