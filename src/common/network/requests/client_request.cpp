
#include "client_request.h"

ClientRequestType
ClientRequest::get_client_request_type_from_message_type_string(
    const std::string message_type) {
    if (message_type == "join") {
        return ClientJoinRequest;
    } else if (message_type == "ready") {
        return ClientReadyRequest;
    } else if (message_type == "prepared") {
        return ClientPreparedRequest;
    } else if (message_type == "shoot") {
        return ClientShootRequest;
    } else if (message_type == "give_up") {
        return ClientGiveUpRequest;
    } else {
        return ClientUnknownRequest;
    }
}

ClientRequest::ClientRequest(const json& data) {
    // Use the JSON data to initialize the member variables

    // set the message type
    if (data.contains("message_type") && data["message_type"].is_string()) {
        std::string message_type = data["message_type"];
        _type = get_client_request_type_from_message_type_string(message_type);

        // a player join request doesn't need a player_id or game_id
        if (_type == ClientJoinRequest) {
            return;
        }

        if (data.contains("game_id") && data["game_id"].is_string()) {
            _game_id = data["game_id"];

            if (data.contains("player_id") && data["player_id"].is_string()) {
                _player_id = data["player_id"];
            } else {
                throw std::runtime_error("Invalid player_id");
            }
        } else {
            throw std::runtime_error("Invalid game_id");
        }
    } else {
        throw std::runtime_error("Invalid message_type");
    }
}

ClientRequestType ClientRequest::get_type() const { return _type; }

std::string ClientRequest::get_player_id() const { return _player_id; }

std::string ClientRequest::get_game_id() const { return _game_id; }
