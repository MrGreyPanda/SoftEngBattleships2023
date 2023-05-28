#pragma once

#include <string>

#include "base_message.h"

/**
 * @brief message class for all messages that are sent from the server
 * to the client without a request from the client
 */
class Message : public BaseMessage {
   public:
    Message(const json& data);
    Message(const MessageType& type, const std::string& game_id,
            const std::string& player_id);

    /**
     * @brief Get the game id of this message
     *
     * @return std::string
     */
    std::string get_game_id() const;

    /**
     * @brief Get the player_id string of this message
     *
     * @return std::string
     */
    std::string get_player_id() const;

    /**
     * @brief Get the JSON representation of this message
     *
     * @return json
     */
    virtual json to_json() const override;

   private:
    std::string player_id_;
    std::string game_id_;
};