#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

enum ServerResponseType { RequestResponse, FullStateMessage };

class ServerResponse {
   public:
    ServerResponse(const json& data);

    std::string get_game_id() const;

   private:
    const ServerResponseType _type;
    const std::string _game_id;
};