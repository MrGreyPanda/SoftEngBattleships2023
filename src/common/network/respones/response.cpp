#include "response.h"

Response::Response(const json& data) : Message(data) {
    if (data.contains("error")) error_ = data["error"];
}

Response::Response(const MessageType& type, const std::string& game_id,
                   const std::string& player_id)
    : Message(type, game_id, player_id) {}

Response::Response(const MessageType& type, const std::string& game_id,
                   const std::string& player_id, const std::string& error)
    : Message(type, game_id, player_id), error_(error) {}

std::string Response::get_error() const { return error_; }

json Response::to_json() const {
    json j = Message::to_json();
    if (!error_.empty()) j["error"] = error_;
    return j;
}