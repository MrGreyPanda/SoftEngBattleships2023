#include "prepared_request.h"

PreparedRequest::PreparedRequest()
    : Message(MessageType::PreparedRequestType) {}

PreparedRequest::PreparedRequest(const json& data) : Message(data) {
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

PreparedRequest::PreparedRequest(const std::string& game_id,
                                 const std::string& player_id,
                                 const std::vector<Ship>& ships)
    : Message(MessageType::PreparedRequestType, game_id, player_id) {
    // convert ships to ship data
    ships_ = std::vector<ShipData>(0);
    for (const Ship& ship : ships) {
        ships_.push_back(ship.get_data());
    }
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