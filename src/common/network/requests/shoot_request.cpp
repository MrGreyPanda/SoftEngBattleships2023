#include "shoot_request.h"

ShootRequest::ShootRequest(const json& data) : Message(data) {
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

ShootRequest::ShootRequest(std::string game_id, std::string player_id,
                           unsigned short x, unsigned short y)
    : Message(MessageType::ShootRequestType, game_id, player_id),
      x_(x),
      y_(y) {}

json ShootRequest::to_json() const {
    json data = Message::to_json();
    data["x"] = x_;
    data["y"] = y_;
    return data;
}

unsigned short ShootRequest::get_x() const { return x_; }

unsigned short ShootRequest::get_y() const { return y_; }