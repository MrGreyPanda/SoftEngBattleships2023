#pragma once

#include <nlohmann/json.hpp>

#include "message_types.h"

using json = nlohmann::json;

class BaseMessage {
   public:
    BaseMessage(const json& type);
    BaseMessage(const MessageType& type);

    /**
     * @brief Get the type of this message
     *
     * @return MessageType
     */
    virtual MessageType get_type() const;

    /**
     * @brief Get the JSON representation of this message
     *
     * @return json
     */
    virtual json to_json() const;

    /**
     * @brief Get the JSON string representation of this message
     *
     * @param data
     */
    virtual std::string to_string() const;

   private:
    MessageType type_;
};
