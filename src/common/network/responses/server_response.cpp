#include "server_response.h"

ServerResponseType _get_server_request_type_from_message_type_string(
    std::string message_type_string) {
    if (message_type_string == "response") {
        return ServerResponseType::RequestResponse;
    } else if (message_type_string == "full_state") {
        return ServerResponseType::FullStateMessage;
    } else {
        throw std::runtime_error("Invalid message type");
    }
}

ServerResponse::ServerResponse(const json& data) {
    // Use the JSON data to initialize the member variables

    // set the message type
    if (data.contains("message_type") && data["message_type"].is_string()) {
        std::string message_type = data["message_type"];
        _type =
            _get_server_request_type_from_message_type_string(message_type);

        if (data.contains("game_id") && data["game_id"].is_string()) {
            _game_id = data["game_id"];
        } else {
            throw std::runtime_error("Invalid game_id");
        }
    } else {
        throw std::runtime_error("Invalid message_type");
    }

    throw std::runtime_error("Not implemented");
}

ServerResponse::ServerResponse(const ServerResponseType type,
                               const std::string& game_id)
    : _type(type), _game_id(game_id) {}

ServerResponse::ServerResponse(const ServerResponseType type,
                               const std::string& game_id,
                               const std::string& error_message)
    : _type(type), _game_id(game_id), _error_message(error_message) {}

std::string ServerResponse::get_game_id() const { return _game_id; }

json ServerResponse::to_json() const {
    json data;
    data["message_type"] = "response";
    data["game_id"]      = _game_id;

    if (!_error_message.empty()) data["error"] = _error_message;

    return data;
}