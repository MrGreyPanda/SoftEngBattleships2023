#pragma once

#include "prepared_request.h"
#include "response.h"

class PreparedResponse : public Response, public PreparedRequest {
   public:
    PreparedResponse(const json& data);
    PreparedResponse(const std::string& game_id, const std::string& player_id,
                     const std::vector<ShipData>& ship_data,
                     const bool& is_valid);
    PreparedResponse(const std::string& game_id, const std::string& player_id,
                     const std::vector<ShipData>& ship_data,
                     const bool& is_valid, const std::string& error);

    json to_json() const override;

    std::string to_string() const override;

    std::string get_game_id() const;

    std::string get_player_id() const;

    MessageType get_type() const;

    bool is_valid() const;

   private:
    bool is_valid_;
};