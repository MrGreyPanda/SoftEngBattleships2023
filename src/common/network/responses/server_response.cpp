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
        std::string message_type = data["message_type"];
        _type = get_server_request_type_from_message_type_string(message_type);

        if (data.contains("request_type") &&
            data["request_type"].is_string()) {
            const std::string request_type_str = data["request_type"];
            _request_type                      = ClientRequest::
                get_client_request_type_from_message_type_string(
                    request_type_str);

            if (data.contains("game_id") && data["game_id"].is_string()) {
                _game_id = data["game_id"];
            }
            if (data.contains("player_id") && data["player_id"].is_string()) {
                _player_id = data["player_id"];
            }
            if (data.contains("error") && data["error"].is_string()) {
                _error_message = data["error"];
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
    : _type(type),
      _request_type(ClientRequestType::ClientUnknownRequest),
      _error_message(error_message) {}

ServerResponse::ServerResponse(const ServerResponseType& type,
                               const ClientRequestType& request_type,
                               const std::string& game_id,
                               const std::string& player_id)
    : _type(type),
      _request_type(request_type),
      _game_id(game_id),
      _player_id(player_id) {}

ServerResponse::ServerResponse(const ServerResponseType& type,
                               const ClientRequestType& request_type,
                               const std::string& game_id,
                               const std::string& player_id,
                               const std::string& error_message)
    : _type(type),
      _request_type(request_type),
      _game_id(game_id),
      _player_id(player_id),
      _error_message(error_message) {}

ServerResponseType ServerResponse::get_type() const { return _type; }

ClientRequestType ServerResponse::get_request_type() const {
    return _request_type;
}

std::string ServerResponse::get_game_id() const { return _game_id; }

std::string ServerResponse::get_player_id() const { return _player_id; }

json ServerResponse::to_json() const {
    json data;

    // set message type
    for (auto& it : server_response_type_map) {
        if (it.second == _type) {
            data["message_type"] = it.first;
            break;
        }
    }

    // set request type
    for (auto& it : ClientRequest::client_request_type_map) {
        if (it.second == _request_type) {
            data["request_type"] = it.first;
            break;
        }
    }

    data["game_id"]   = _game_id;
    data["player_id"] = _player_id;

    if (!_error_message.empty()) data["error"] = _error_message;

    return data;
}

std::string ServerResponse::to_string() const { return to_json().dump(); }