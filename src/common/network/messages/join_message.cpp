#include "join_message.h"

JoinedMessage::JoinedMessage(const json& data) : Message(data) {}

JoinedMessage::JoinedMessage(const std::string& game_id,
                         const std::string& player_id)
    : Message(MessageType::JoinedMessageType, game_id, player_id) {}
