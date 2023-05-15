
#include "client_request.h"

std::map<std::string, ClientRequestType>
    ClientRequest::client_request_type_map = {{"join", Join},
                                              {"ready", Ready},
                                              {"prepared", Prepared},
                                              {"shoot", Shoot},
                                              {"give_up", GiveUp}};

ClientRequestType
ClientRequest::get_client_request_type_from_message_type_string(
    const std::string message_type_string) {
    auto it = client_request_type_map.find(message_type_string);
    if (it != client_request_type_map.end()) {
        return it->second;
    }
    return ClientRequestType::Unknown;
}

ClientRequest::ClientRequest()
    : type_(Unknown), player_id_(""), game_id_("") {}

ClientRequest::ClientRequest(const json& data) {
    // Use the JSON data to initialize the member variables

    // set the message type
    if (data.contains("message_type") && data["message_type"].is_string()) {
        std::string message_type = data["message_type"].get<std::string>();
        type_ = get_client_request_type_from_message_type_string(message_type);

        // a player join request doesn't need a player_id or game_id
        if (type_ == Join) {
            return;
        }

        if (data.contains("game_id") && data["game_id"].is_string()) {
            game_id_ = data["game_id"].get<std::string>();

            if (data.contains("player_id") && data["player_id"].is_string()) {
                player_id_ = data["player_id"].get<std::string>();
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

ClientRequest::ClientRequest(ClientRequestType type, std::string game_id,
                             std::string player_id)
    : type_(type), player_id_(player_id), game_id_(game_id) {}

ClientRequestType ClientRequest::get_type() const { return type_; }

std::string ClientRequest::get_game_id() const { return game_id_; }

std::string ClientRequest::get_player_id() const { return player_id_; }

json ClientRequest::to_json() const {
    json data;

    // get the string representation of the message type
    for (auto& it : client_request_type_map) {
        if (it.second == type_) {
            data["message_type"] = it.first;
            break;
        }
    }

    if (!game_id_.empty()) {
        data["game_id"] = game_id_;
    }
    if (!player_id_.empty()) {
        data["player_id"] = player_id_;
    }

    return data;
}

std::string ClientRequest::to_string() const { return to_json().dump(); }
