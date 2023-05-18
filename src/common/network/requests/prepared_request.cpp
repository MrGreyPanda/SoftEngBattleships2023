#include "prepared_request.h"

PreparedRequest::PreparedRequest(const json& data) : Message(data) {
    // parse ship data
    ships_ = data.at("ships").get<std::vector<ShipData>>();
}

PreparedRequest::PreparedRequest(const std::string& game_id,
                                 const std::string& player_id,
                                 const std::vector<ShipData>& ship_data)
    : Message(MessageType::PreparedRequestType, game_id, player_id),
      ships_(ship_data) {}

json PreparedRequest::to_json() const {
    json data = Message::to_json();

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

std::vector<ShipData> PreparedRequest::get_ship_data() const { return ships_; }

std::vector<Ship> PreparedRequest::get_ships() const {
    std::vector<Ship> ships(0);
    for (const ShipData& ship_data : ships_) {
        ships.push_back(Ship(ship_data));
    }
    return ships;
}
