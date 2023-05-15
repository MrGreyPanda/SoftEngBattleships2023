#include "client_shoot_request.h"

ClientShootRequest::ClientShootRequest() : ClientRequest() {}

ClientShootRequest::ClientShootRequest(const json& data)
    : ClientRequest(data) {
    if (data.contains("x") && data["x"].is_number_integer()) {
        x_ = data["x"].get<unsigned short>();
    } else {
        throw std::runtime_error("Invalid x");
    }

    if (data.contains("y") && data["y"].is_number_integer()) {
        y_ = data["y"].get<unsigned short>();
    } else {
        throw std::runtime_error("Invalid y");
    }
}

ClientShootRequest::ClientShootRequest(std::string game_id,
                                       std::string player_id, unsigned short x,
                                       unsigned short y)
    : ClientRequest(ClientRequestType::Shoot, game_id, player_id),
      x_(x),
      y_(y) {}

json ClientShootRequest::to_json() const {
    json data = ClientRequest::to_json();
    data["x"] = x_;
    data["y"] = y_;
    return data;
}

unsigned short ClientShootRequest::get_x() const { return x_; }

unsigned short ClientShootRequest::get_y() const { return y_; }