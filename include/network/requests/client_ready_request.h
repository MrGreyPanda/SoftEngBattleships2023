#pragma once

#include "client_request.h"

class ClientReadyRequest : public ClientRequest {
   public:
    ClientReadyRequest();
    ClientReadyRequest(const json& data);
    ClientReadyRequest(std::string game_id, std::string player_id);

    json to_json() const;
};