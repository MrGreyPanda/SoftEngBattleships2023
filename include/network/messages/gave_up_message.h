#pragma once

#include "give_up_request.h"

class GaveUpMessage : public GiveUpRequest {
   public:
    GaveUpMessage(const json& data);
    GaveUpMessage(const std::string& game_id, const std::string& player_id);

    json to_json() const override;

    MessageType get_type() const override;
};
