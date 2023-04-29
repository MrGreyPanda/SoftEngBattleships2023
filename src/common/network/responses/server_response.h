#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "../requests/client_request.h"

enum ServerResponseType { RequestResponse, FullStateMessage };

class ServerResponse {
   public:
    ServerResponse(const json& data);
    ServerResponse(const ServerResponseType& type,
                   const std::string& error_message);
    ServerResponse(const ServerResponseType& type,
                   const ClientRequestType& request_type,
                   const std::string& game_id, const std::string& player_id);
    ServerResponse(const ServerResponseType& type,
                   const ClientRequestType& request_type,
                   const std::string& game_id, const std::string& player_id,
                   const std::string& error_message);

    static ServerResponseType get_server_request_type_from_message_type_string(
        const std::string message_type_string);

    std::string get_game_id() const;

    std::string get_player_id() const;

    json to_json() const;

    std::string to_string() const;

   private:
    ServerResponseType _type;
    ClientRequestType _request_type;
    std::string _game_id;
    std::string _player_id;
    std::string _error_message;
};