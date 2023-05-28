#pragma once

#include <nlohmann/json.hpp>

#include "message_types.h"

using json = nlohmann::json;

/**
 * @brief Base class for all network messages
 */
class BaseMessage {
   public:
    /**
     * @brief JSON constructor
     *
     * @param data JSON data
     */
    BaseMessage(const json& json);

    /**
     * @brief Construct a new base message object using the given type
     *
     * @param type Message type
     */
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
