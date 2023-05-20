#include "shoot_request.h"

ShootRequest::ShootRequest(const json& data) : Message(data) {
    x_ = data.at("x").get<unsigned short>();
    y_ = data.at("y").get<unsigned short>();
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