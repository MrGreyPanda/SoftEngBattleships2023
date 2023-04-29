#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

enum ServerResponseType { RequestResponse, FullStateMessage };

class ServerResponse {
   public:
    ServerResponse(const json& data);
    ServerResponse(const ServerResponseType type, const std::string& game_id);
    ServerResponse(const ServerResponseType type, const std::string& game_id,
                   const std::string& error_message);

    std::string get_game_id() const;

    json to_json() const;

   private:
    ServerResponseType _type;
    std::string _game_id;
    std::string _error_message;
};