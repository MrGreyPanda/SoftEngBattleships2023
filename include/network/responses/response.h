#pragma once

#include "message.h"

class Response : public Message {
   public:
    Response(const json& data);
    Response(const MessageType& type, const std::string& game_id,
             const std::string& player_id);
    Response(const MessageType& type, const std::string& game_id,
             const std::string& player_id, const std::string& error);

    std::string get_error() const;

   private:
    std::string error_;
};
