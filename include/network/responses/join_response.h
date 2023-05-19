#pragma once

#include "join_request.h"
#include "response.h"

class JoinResponse : public Response {
   public:
    JoinResponse(const json& data);
    JoinResponse(const std::string& game_id, const std::string& player_id,
                 const unsigned player_amount);
    JoinResponse(const std::string& game_id, const std::string& player_id,
                 const std::string& error, const unsigned player_amount);

    json to_json() const override;

    const unsigned get_player_amount() const;
    void set_player_amount(unsigned player_amount);

   private:
      unsigned player_amount_ = 0;
};
