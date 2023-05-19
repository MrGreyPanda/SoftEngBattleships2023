#include "shoot_request.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(ShootRequestTest, JSONConstructor) {
    json shoot_req_json = HelperFunctions::load_json_from_file(
        "../json_examples/requests/shoot_request.json");

    ShootRequest shoot_request(shoot_req_json);

    EXPECT_EQ(shoot_request.get_type(), MessageType::ShootRequestType);
    EXPECT_EQ(shoot_request.get_game_id(),
              shoot_req_json.at("game_id").get<std::string>());
    EXPECT_EQ(shoot_request.get_player_id(),
              shoot_req_json.at("player_id").get<std::string>());
    EXPECT_EQ(shoot_request.get_x(),
              shoot_req_json.at("x").get<unsigned short>());
    EXPECT_EQ(shoot_request.get_y(),
              shoot_req_json.at("y").get<unsigned short>());
}

TEST(ShootRequestTest, Constructor) {
    std::string game_id   = "test_shoot_req_game_id";
    std::string player_id = "test_shoot_req_player_id";
    unsigned short x      = 1;
    unsigned short y      = 2;

    ShootRequest shoot_request(game_id, player_id, x, y);

    EXPECT_EQ(shoot_request.get_type(), MessageType::ShootRequestType);
    EXPECT_EQ(shoot_request.get_game_id(), game_id);
    EXPECT_EQ(shoot_request.get_player_id(), player_id);
    EXPECT_EQ(shoot_request.get_x(), x);
    EXPECT_EQ(shoot_request.get_y(), y);
}

TEST(ShootRequestTest, to_json) {
    json shoot_req_json = HelperFunctions::load_json_from_file(
        "../json_examples/requests/shoot_request.json");

    ShootRequest shoot_request(shoot_req_json);

    json shoot_req_json_2 = shoot_request.to_json();

    EXPECT_EQ(shoot_req_json, shoot_req_json_2);
}