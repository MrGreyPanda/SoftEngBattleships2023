#pragma once

#include "message.h"

class JoinedMessage : public Message {
   public:
    JoinedMessage(const json& data);
    JoinedMessage(const std::string& game_id, const std::string& player_id,
                  const unsigned& number_of_players);

    json to_json() const override;

    unsigned get_number_of_players() const;

   private:
    unsigned number_of_players_;
};
