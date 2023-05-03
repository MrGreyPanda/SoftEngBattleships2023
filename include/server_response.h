#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "client_request.h"

enum ServerResponseType { Unknown, RequestResponse, FullStateMessage };

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

    ServerResponseType get_type() const;

    ClientRequestType get_request_type() const;

    std::string get_game_id() const;

    std::string get_player_id() const;

    json to_json() const;

    std::string to_string() const;

    static std::map<std::string, ServerResponseType> server_response_type_map;

   private:
    ServerResponseType type_;
    ClientRequestType request_type_;
    std::string game_id_;
    std::string player_id_;
    std::string error_message_;
};