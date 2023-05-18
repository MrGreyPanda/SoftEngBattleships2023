#include "shot_message.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(ShotMessage, JSONConstructor) {
    json shot_msg_json = HelperFunctions::load_json_from_file(
        "../json_examples/messages/shot_message.json");

    ShotMessage shot_message(shot_msg_json);

    EXPECT_EQ(shot_message.get_type(), MessageType::ShotMessageType);
    EXPECT_EQ(shot_message.get_game_id(),
              shot_msg_json.at("game_id").get<std::string>());
    EXPECT_EQ(shot_message.get_player_id(),
              shot_msg_json.at("player_id").get<std::string>());
    EXPECT_EQ(shot_message.get_x(),
              shot_msg_json.at("x").get<unsigned short>());
    EXPECT_EQ(shot_message.get_y(),
              shot_msg_json.at("y").get<unsigned short>());
    EXPECT_EQ(shot_message.has_hit(), shot_msg_json.at("has_hit").get<bool>());
}

TEST(ShotMessage, Constructor) {
    std::string game_id   = "test_shot_msg_game_id";
    std::string player_id = "test_shot_msg_player_id";
    unsigned short x      = 1;
    unsigned short y      = 2;
    bool has_hit          = false;

    ShotMessage shot_message(game_id, player_id, x, y, has_hit);

    EXPECT_EQ(shot_message.get_type(), MessageType::ShotMessageType);
    EXPECT_EQ(shot_message.get_game_id(), game_id);
    EXPECT_EQ(shot_message.get_player_id(), player_id);
    EXPECT_EQ(shot_message.get_x(), x);
    EXPECT_EQ(shot_message.get_y(), y);
    EXPECT_EQ(shot_message.has_hit(), has_hit);
}

TEST(ShotMessage, to_json) {
    json shot_msg_json = HelperFunctions::load_json_from_file(
        "../json_examples/messages/shot_message.json");

    ShotMessage shot_message(shot_msg_json);

    json shot_msg_json_2 = shot_message.to_json();

    EXPECT_EQ(shot_msg_json, shot_msg_json_2);
}