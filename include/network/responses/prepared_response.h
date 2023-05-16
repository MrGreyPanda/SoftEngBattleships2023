#pragma once

#include "prepared_request.h"
#include "response.h"

class PreparedResponse : public Response, PreparedRequest {
   public:
    PreparedResponse(const json& data);
    PreparedResponse(const std::string& game_id, const std::string& player_id,
                     const std::vector<Ship>& ships);
    PreparedResponse(const std::string& game_id, const std::string& player_id,
                     const std::vector<Ship>& ships, const std::string& error);
    PreparedResponse(const std::string& game_id, const std::string& player_id,
                     const std::vector<ShipData>& ship_data);
    PreparedResponse(const std::string& game_id, const std::string& player_id,
                     const std::vector<ShipData>& ship_data,
                     const std::string& error);

    json to_json() const override;

    std::string to_string() const override;

    std::string get_game_id() const;

    std::string get_player_id() const;
};