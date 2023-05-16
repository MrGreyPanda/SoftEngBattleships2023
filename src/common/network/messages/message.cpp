#include "message.h"

Message::Message(const json& data) : BaseMessage(data) {
    game_id_   = data["game_id"];
    player_id_ = data["player_id"];
}

Message::Message(const MessageType& type, const std::string& game_id,
                 const std::string& player_id)
    : BaseMessage(type), game_id_(game_id), player_id_(player_id) {}

std::string Message::get_game_id() const { return game_id_; }

std::string Message::get_player_id() const { return player_id_; }

json Message::to_json() const {
    json j         = BaseMessage::to_json();
    j["game_id"]   = game_id_;
    j["player_id"] = player_id_;
    return j;
}