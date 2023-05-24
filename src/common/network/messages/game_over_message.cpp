#include "game_over_message.h"

#include "helper_functions.h"

GameOverMessage::GameOverMessage(const json& data) : PreparedRequest(data) {
    has_won_ = data.at("has_won");
}

GameOverMessage::GameOverMessage(const std::string& game_id,
                                 const std::string& player_id,
                                 const bool& has_won)
    : PreparedRequest(game_id, player_id,
                      HelperFunctions::get_funny_ship_configuration()),
      has_won_(has_won) {}

GameOverMessage::GameOverMessage(const std::string& game_id,
                                 const std::string& player_id,
                                 const bool& has_won,
                                 std::array<ShipData, 5> ship_config)
    : PreparedRequest(game_id, player_id, ship_config), has_won_(has_won) {}

json GameOverMessage::to_json() const {
    json j       = PreparedRequest::to_json();
    j["type"]    = "game_over_message";
    j["has_won"] = has_won_;
    return j;
}

MessageType GameOverMessage::get_type() const {
    return MessageType::GameOverMessageType;
}

bool GameOverMessage::has_won() const { return has_won_; }