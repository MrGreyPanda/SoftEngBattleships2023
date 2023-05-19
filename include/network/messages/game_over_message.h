#pragma once

#include "prepared_request.h"

class GameOverMessage : public PreparedRequest {
   public:
    GameOverMessage(const json& data);
    GameOverMessage(const std::string& game_id, const std::string& player_id,
                    const bool& has_won, std::array<ShipData, 5> ship_config);

    json to_json() const;

    MessageType get_type() const;

    bool has_won() const;

   private:
    bool has_won_;
};
