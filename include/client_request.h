#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

enum ClientRequestType {
    ClientUnknownRequest,
    ClientJoinRequest,
    ClientReadyRequest,
    ClientPreparedRequest,
    ClientShootRequest,
    ClientGiveUpRequest
};

class ClientRequest {
   public:
    ClientRequest(const json& data);
    ClientRequest(ClientRequestType type, std::string player_id = "",
                  std::string game_id = "");

    static ClientRequestType get_client_request_type_from_message_type_string(
        const std::string message_type_string);

    /**
     * @brief Get the type of this ClientRequest
     *
     * @return ClientRequestType
     */
    ClientRequestType get_type() const;

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

    json to_json() const;

    std::string to_string() const;

    static std::map<std::string, ClientRequestType> client_request_type_map;

   private:
    ClientRequestType type_;
    std::string game_id_;
    std::string player_id_;
};