#include "client_prepared_request.h"

ClientPreparedRequest::ClientPreparedRequest() : ClientRequest() {}

ClientPreparedRequest::ClientPreparedRequest(const json& data)
    : ClientRequest(data) {
    // parse ship data

    // create empty ship data vector
    ships_ = std::vector<ShipData>(0);
    for (auto& ship_data_json : data["ships"]) {
        ShipData ship_data;
        ship_data.name          = ship_data_json["name"];
        ship_data.is_horizontal = ship_data_json["is_horizontal"];
        ship_data.x             = ship_data_json["x"];
        ship_data.y             = ship_data_json["y"];

        ships_.push_back(ship_data);
    }
}

ClientPreparedRequest::ClientPreparedRequest(const std::string& game_id,
                                             const std::string& player_id,
                                             const std::vector<Ship>& ships)
    : ClientRequest(ClientRequestType::Prepared, game_id, player_id) {
    // convert ships to ship data
    ships_ = std::vector<ShipData>(0);
    for (const Ship& ship : ships) {
        ships_.push_back(ship.get_data());
    }
}

ClientPreparedRequest::ClientPreparedRequest(
    const std::string& game_id, const std::string& player_id,
    const std::vector<ShipData>& ship_data)
    : ClientRequest(ClientRequestType::Prepared, game_id, player_id),
      ships_(ship_data) {}

json ClientPreparedRequest::to_json() const {
    json data = ClientRequest::to_json();

    // convert ship data to json
    json ships_json = json::array();
    for (const ShipData& ship_data : ships_) {
        json ship_data_json;
        ship_data_json["name"]          = ship_data.name;
        ship_data_json["is_horizontal"] = ship_data.is_horizontal;
        ship_data_json["x"]             = ship_data.x;
        ship_data_json["y"]             = ship_data.y;

        ships_json.push_back(ship_data_json);
    }

    data["ships"] = ships_json;

    return data;
}