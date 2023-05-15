#pragma once

#include "message.h"

class Response : public Message {
    Response(const json& data);
    Response(const MessageType& type, std::string game_id,
             std::string player_id);
    Response(const MessageType& type, std::string game_id,
             std::string player_id, std::string error);

    std::string get_error() const;

   private:
    std::string error_;
};
