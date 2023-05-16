#include "ready_message.h"

ReadyMessage::ReadyMessage(const json& data) : Message(data) {}

ReadyMessage::ReadyMessage(const std::string& game_id,
                           const std::string& player_id)
    : Message(MessageType::ReadyMessageType, game_id, player_id) {}
