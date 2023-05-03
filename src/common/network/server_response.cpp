#include "server_response.h"

std::map<std::string, ServerResponseType>
    ServerResponse::server_response_type_map = {
        {"response", RequestResponse},
        {"full_state", FullStateMessage},
};

ServerResponseType
ServerResponse::get_server_request_type_from_message_type_string(
    std::string message_type_string) {
    auto it = server_response_type_map.find(message_type_string);
    if (it != server_response_type_map.end()) {
        return it->second;
    }
    return ServerResponseType::Unknown;
}

ServerResponse::ServerResponse(const json& data) {
    // Use the JSON data to initialize the member variables

    // set the message type
    if (data.contains("message_type") && data["message_type"].is_string()) {
        std::string message_type = data["message_type"].get<std::string>();
        type_ = get_server_request_type_from_message_type_string(message_type);

        if (data.contains("request_type") &&
            data["request_type"].is_string()) {
            const std::string request_type_str =
                data["request_type"].get<std::string>();
            request_type_ = ClientRequest::
                get_client_request_type_from_message_type_string(
                    request_type_str);

            if (data.contains("game_id") && data["game_id"].is_string()) {
                game_id_ = data["game_id"].get<std::string>();
            }
            if (data.contains("player_id") && data["player_id"].is_string()) {
                player_id_ = data["player_id"].get<std::string>();
            }
            if (data.contains("error") && data["error"].is_string()) {
                error_message_ = data["error"].get<std::string>();
            }
        } else {
            throw std::runtime_error("Invalid request_type");
        }

    } else {
        throw std::runtime_error("Invalid message_type");
    }
}

ServerResponse::ServerResponse(const ServerResponseType& type,
                               const std::string& error_message)
    : type_(type),
      request_type_(ClientRequestType::ClientUnknownRequest),
      error_message_(error_message) {}

ServerResponse::ServerResponse(const ServerResponseType& type,
                               const ClientRequestType& request_type,
                               const std::string& game_id,
                               const std::string& player_id)
    : type_(type),
      request_type_(request_type),
      game_id_(game_id),
      player_id_(player_id) {}

ServerResponse::ServerResponse(const ServerResponseType& type,
                               const ClientRequestType& request_type,
                               const std::string& game_id,
                               const std::string& player_id,
                               const std::string& error_message)
    : type_(type),
      request_type_(request_type),
      game_id_(game_id),
      player_id_(player_id),
      error_message_(error_message) {}

ServerResponseType ServerResponse::get_type() const { return type_; }

ClientRequestType ServerResponse::get_request_type() const {
    return request_type_;
}

std::string ServerResponse::get_game_id() const { return game_id_; }

std::string ServerResponse::get_player_id() const { return player_id_; }

json ServerResponse::to_json() const {
    json data;

    // set message type
    for (auto& it : server_response_type_map) {
        if (it.second == type_) {
            data["message_type"] = it.first;
            break;
        }
    }

    // set request type
    for (auto& it : ClientRequest::client_request_type_map) {
        if (it.second == request_type_) {
            data["request_type"] = it.first;
            break;
        }
    }

    data["game_id"]   = game_id_;
    data["player_id"] = player_id_;

    if (!error_message_.empty()) data["error"] = error_message_;

    return data;
}

std::string ServerResponse::to_string() const { return to_json().dump(); }