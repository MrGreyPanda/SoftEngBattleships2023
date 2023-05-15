#include "base_message.h"

BaseMessage::BaseMessage(const MessageType& type) : type_(type) {}

MessageType BaseMessage::get_type() const { return type_; }

json BaseMessage::to_json() const {
    json j;
    j["type"] = type_;
    return j;
}

std::string BaseMessage::to_string() const { return to_json().dump(); }