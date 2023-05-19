#include "join_response.h"

JoinResponse::JoinResponse(const json& data) 
    : Response(data) {
        if (data.contains("player_amount")) player_amount_ = data["player_amount"];
    }

JoinResponse::JoinResponse(const std::string& game_id,
                           const std::string& player_id,
                           const unsigned player_amount)
    : Response(MessageType::JoinResponseType, game_id, player_id),
        player_amount_(player_amount) {}

JoinResponse::JoinResponse(const std::string& game_id,
                           const std::string& player_id,
                           const std::string& error,
                           const unsigned player_amount)
    : Response(MessageType::JoinResponseType, game_id, player_id, error),
        player_amount_(player_amount) {}

json JoinResponse::to_json() const {
    json j         = Message::to_json();
    j["player_amount"] = player_amount_;
    return j;
}

const unsigned JoinResponse::get_player_amount() const {
    return player_amount_;
}

void JoinResponse::set_player_amount(unsigned player_amount) {
    player_amount_ = player_amount;
}