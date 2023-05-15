#pragma once

#include "client_request.h"

class ClientShootRequest : public ClientRequest {
   public:
    ClientShootRequest();
    ClientShootRequest(const json& data);
    ClientShootRequest(std::string game_id, std::string player_id,
                       unsigned short x_coordinate,
                       unsigned short y_coordinate);

    unsigned short get_x() const;
    unsigned short get_y() const;

    json to_json() const;

   private:
    unsigned short x_;
    unsigned short y_;
};
