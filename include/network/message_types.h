#pragma once

#include <map>
#include <string>

enum MessageType {
    JoinRequestType,
    ReadyRequestType,
    PreparedRequestType,
    ShootRequestType,
    GiveUpRequestType,

    // messages
    JoinedMessageType,
    ReadyMessageType,
    PreparedMessageType,
    ShotMessageType,
    GaveUpMessageType,
    // other messages
    StartGameMessageType,
    StartBattleMessageType,
    TurnMessageType,
    GameOverMessageType,

    // responses
    JoinResponseType,
    ReadyResponseType,
    PreparedResponseType,
    ShootResponseType,
    GiveUpResponseType,

    // unkown
    UnknownType,
};

class MessageTypeHelpers {
   public:
    /*
     * @brief Converts a string to a message type
     *
     * @param type
     * @return MessageType
     */
    static MessageType make_message_type_from_string(
        const std::string& string);

    /*
     * @brief Converts a message type to a string
     *
     * @param type
     * @return std::string
     */
    static std::string make_string_from_message_type(const MessageType& type);

   private:
    static std::map<std::string, MessageType> message_type_map_;
};
