#pragma once

#include "message.h"
#include "ship.h"

class PreparedRequest : public Message {
   public:
    PreparedRequest(const json& data);
    PreparedRequest(const std::string& game_id, const std::string& player_id,
                    const std::array<ShipData, 5>& ship_data);

    virtual json to_json() const override;

    std::array<ShipData, 5> get_ship_data() const;

   private:
    std::array<ShipData, 5> ships_;
};