#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

enum ClientRequestType {
    ClientJoinRequest,
    ClientReadyRequest,
    ClientPreparedRequest,
    ClientShootRequest,
    ClientGiveUpRequest
};

class ClientRequest {
   public:
    ClientRequest(const json& data);

    /**
     * @brief Get the player_id string from this ClientRequest
     *
     * @return std::string
     */
    std::string get_player_id() const;

    /**
     * @brief Get the game id from this ClientRequest
     *
     * @return std::string
     */
    std::string get_game_id() const;

   private:
    ClientRequestType _type;
    std::string _game_id;
    std::string _player_id;
};