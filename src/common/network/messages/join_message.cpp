#include "join_message.h"

JoinMessage::JoinMessage(const json& data) : Message(data) {}

JoinMessage::JoinMessage(const std::string& game_id,
                         const std::string& player_id)
    : Message(MessageType::JoinedMessageType, game_id, player_id) {}
