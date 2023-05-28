#pragma once

#include "message.h"

/**
 * @brief A message sent from the server to the client as a response to a
 * request. This class is used as a base to inhert from for other responses.
 */
class Response : public Message {
   public:
    Response(const json& data);
    Response(const MessageType& type, const std::string& game_id,
             const std::string& player_id);
    Response(const MessageType& type, const std::string& game_id,
             const std::string& player_id, const std::string& error);

    std::string get_error() const;

    virtual json to_json() const override;

   private:
    std::string error_;
};
