#include "prepared_message.h"

PreparedMessage::PreparedMessage(const json& data) : Message(data) {}

PreparedMessage::PreparedMessage(const std::string& game_id,
                                 const std::string& player_id)
    : Message(MessageType::PreparedMessageType, game_id, player_id) {}
