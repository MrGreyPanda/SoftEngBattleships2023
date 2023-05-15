#pragma once

#include <string>

#include "base_message.h"

class Message : public BaseMessage {
   public:
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
    json to_json() const;

    /**
     * @brief Get the string representation of this message
     *
     * @return std::string
     */
    std::string to_string() const;

   private:
    std::string player_id_;
    std::string game_id_;
};