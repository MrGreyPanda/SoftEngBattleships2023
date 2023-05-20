#include "base_message.h"

BaseMessage::BaseMessage(const json& data) {
    type_ = MessageTypeHelpers::make_message_type_from_string(
        data.at("type").get<std::string>());
}

BaseMessage::BaseMessage(const MessageType& type) : type_(type) {}

MessageType BaseMessage::get_type() const { return type_; }

json BaseMessage::to_json() const {
    json j;
    j["type"] = MessageTypeHelpers::make_string_from_message_type(type_);
    return j;
}

std::string BaseMessage::to_string() const { return to_json().dump(); }