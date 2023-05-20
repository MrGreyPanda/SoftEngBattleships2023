#include "prepared_request.h"

PreparedRequest::PreparedRequest(const json& data) : Message(data) {
    // parse ship data
    ships_ = data.at("ships").get<std::array<ShipData, 5>>();
}

PreparedRequest::PreparedRequest(const std::string& game_id,
                                 const std::string& player_id,
                                 const std::array<ShipData, 5>& ship_data)
    : Message(MessageType::PreparedRequestType, game_id, player_id),
      ships_(ship_data) {}

json PreparedRequest::to_json() const {
    json data     = Message::to_json();
    data["ships"] = ships_;

    return data;
}

std::array<ShipData, 5> PreparedRequest::get_ship_data() const {
    return ships_;
}
