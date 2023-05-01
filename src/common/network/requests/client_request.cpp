
#include "client_request.h"

std::map<std::string, ClientRequestType>
    ClientRequest::client_request_type_map = {
        {"join", ClientJoinRequest},
        {"ready", ClientReadyRequest},
        {"prepared", ClientPreparedRequest},
        {"shoot", ClientShootRequest},
        {"give_up", ClientGiveUpRequest}};

ClientRequestType
ClientRequest::get_client_request_type_from_message_type_string(
    const std::string message_type_string) {
    auto it = client_request_type_map.find(message_type_string);
    if (it != client_request_type_map.end()) {
        return it->second;
    }
    return ClientRequestType::ClientUnknownRequest;
}

ClientRequest::ClientRequest(const json& data) {
    // Use the JSON data to initialize the member variables

    // set the message type
    if (data.contains("message_type") && data["message_type"].is_string()) {
        std::string message_type = data["message_type"].get<std::string>();
        _type = get_client_request_type_from_message_type_string(message_type);

        // a player join request doesn't need a player_id or game_id
        if (_type == ClientJoinRequest) {
            return;
        }

        if (data.contains("game_id") && data["game_id"].is_string()) {
            _game_id = data["game_id"].get<std::string>();

            if (data.contains("player_id") && data["player_id"].is_string()) {
                _player_id = data["player_id"].get<std::string>();
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

json ClientRequest::to_json() const {
    json data;

    // get the string representation of the message type
    for (auto& it : client_request_type_map) {
        if (it.second == _type) {
            data["message_type"] = it.first;
            break;
        }
    }

    data["game_id"]   = _game_id;
    data["player_id"] = _player_id;

    return data;
}

std::string ClientRequest::to_string() const { return to_json().dump(); }
