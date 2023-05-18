#include "shoot_response.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(ShootResponse, JSONConstructor) {
    json shoot_resp_json = HelperFunctions::load_json_from_file(
        "../json_examples/responses/shoot_response.json");

    ShootResponse shoot_response(shoot_resp_json);

    EXPECT_EQ(shoot_response.get_type(), MessageType::ShootResponseType);
    EXPECT_EQ(shoot_response.get_game_id(),
              shoot_resp_json.at("game_id").get<std::string>());
    EXPECT_EQ(shoot_response.get_player_id(),
              shoot_resp_json.at("player_id").get<std::string>());
    EXPECT_EQ(shoot_response.get_x(),
              shoot_resp_json.at("x").get<unsigned short>());
    EXPECT_EQ(shoot_response.get_y(),
              shoot_resp_json.at("y").get<unsigned short>());
    EXPECT_EQ(shoot_response.has_hit(),
              shoot_resp_json.at("has_hit").get<bool>());
    EXPECT_EQ(shoot_response.is_valid(),
              shoot_resp_json.at("is_valid").get<bool>());
    EXPECT_EQ(shoot_response.has_destroyed_ship(),
              shoot_resp_json.at("has_destroyed_ship").get<bool>());
    EXPECT_EQ(shoot_response.get_destroyed_ship(),
              shoot_resp_json.at("destroyed_ship").get<ShipData>());
    EXPECT_EQ(shoot_response.get_error(),
              shoot_resp_json.at("error").get<std::string>());
}

TEST(ShootResponse, Constructor) {
    std::string game_id     = "test_shoot_resp_game_id";
    std::string player_id   = "test_shoot_resp_player_id";
    unsigned short x        = 1;
    unsigned short y        = 2;
    bool is_valid           = true;
    bool has_hit            = true;
    bool has_destroyed_ship = true;
    ShipData destroyed_ship(ShipCategory::Submarine, true, 4, 6);
    std::string error = "test_shoot_resp_error";

    ShootResponse shoot_response(game_id, player_id, x, y, destroyed_ship);

    EXPECT_EQ(shoot_response.get_type(), MessageType::ShootResponseType);
    EXPECT_EQ(shoot_response.get_game_id(), game_id);
    EXPECT_EQ(shoot_response.get_player_id(), player_id);
    EXPECT_EQ(shoot_response.get_x(), x);
    EXPECT_EQ(shoot_response.get_y(), y);
    EXPECT_EQ(shoot_response.has_hit(), has_hit);
    EXPECT_EQ(shoot_response.is_valid(), is_valid);
    EXPECT_EQ(shoot_response.has_destroyed_ship(), has_destroyed_ship);
    EXPECT_EQ(shoot_response.get_destroyed_ship(), destroyed_ship);
    EXPECT_EQ(shoot_response.get_error(), error);
}

TEST(ShootResponse, to_json) {
    json shoot_resp_json = HelperFunctions::load_json_from_file(
        "../json_examples/responses/shoot_response.json");

    ShootResponse shoot_response(shoot_resp_json);

    json shoot_resp_json_2 = shoot_response.to_json();

    EXPECT_EQ(shoot_resp_json, shoot_resp_json_2);
}