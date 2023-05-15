#include "message_types.h"

std::map<std::string, MessageType> MessageTypeHelpers::message_type_map_ = {
    // requests
    {"join_request", JoinRequestType},
    {"ready_request", ReadyRequestType},
    {"prepared_request", PreparedRequestType},
    {"shoot_request", ShootRequestType},
    {"give_up_request", GiveUpRequestType},

    // messages
    {"joined_message", JoinedMessageType},
    {"ready_message", ReadyMessageType},
    {"prepared_message", PreparedMessageType},
    {"shot_message", ShotMessageType},
    {"gave_up_message", GaveUpMessageType},
    // other messages
    {"start_game_message", StartGameMessageType},
    {"start_battle_message", StartBattleMessageType},
    {"turn_message", TurnMessageType},
    {"shot_message", ShotMessageType},
    {"end_message", EndMessageType},

    // responses
    {"join_response", JoinResponseType},
    {"ready_response", ReadyResponseType},
    {"prepared_response", PreparedResponseType},
    {"shoot_response", ShootResponseType},
    {"give_up_response", GiveUpResponseType},

    // unkown
    {"unknown_type", UnknownType},
};

MessageType MessageTypeHelpers::make_message_type_from_string(
    const std::string &string) {
    auto it = message_type_map_.find(string);
    if (it != message_type_map_.end()) {
        return it->second;
    }
    return MessageType::UnknownType;
}

std::string MessageTypeHelpers::make_string_from_message_type(
    const MessageType &type) {
    for (auto &it : message_type_map_) {
        if (it.second == type) {
            return it.first;
        }
    }
    return "unknown_type";
}