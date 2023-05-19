#include "gave_up_message.h"

GaveUpMessage::GaveUpMessage(const json& data) : GiveUpRequest(data) {}

GaveUpMessage::GaveUpMessage(const std::string& game_id,
                             const std::string& player_id)
    : GiveUpRequest(game_id, player_id) {}

json GaveUpMessage::to_json() const {
    json j    = GiveUpRequest::to_json();
    j["type"] = "gave_up_message";
    return j;
}

MessageType GaveUpMessage::get_type() const {
    return MessageType::GaveUpMessageType;
}
