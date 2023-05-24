#include "join_message.h"

JoinedMessage::JoinedMessage(const json& data) : Message(data) {
    number_of_players_ = data.at("number_of_players");
}

JoinedMessage::JoinedMessage(const std::string& game_id,
                             const std::string& player_id,
                             const unsigned& number_of_players)
    : Message(MessageType::JoinedMessageType, game_id, player_id),
      number_of_players_(number_of_players) {}

json JoinedMessage::to_json() const {
    json j                 = Message::to_json();
    j["number_of_players"] = number_of_players_;
    return j;
}

unsigned JoinedMessage::get_number_of_players() const {
    return number_of_players_;
}
