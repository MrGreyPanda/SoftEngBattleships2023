#include "give_up_request.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(GiveUpRequest, JSONConstructor) {
    json j = HelperFunctions::load_json_from_file(
        "../json_examples/requests/give_up_request.json");

    GiveUpRequest give_up_request(j);
    EXPECT_EQ(give_up_request.get_type(), MessageType::GiveUpRequestType);
    EXPECT_EQ(give_up_request.get_game_id(), j.at("game_id"));
    EXPECT_EQ(give_up_request.get_player_id(), j.at("player_id"));
}

TEST(GiveUpRequest, Constructor) {
    GiveUpRequest give_up_request("game_id", "player_id");
    EXPECT_EQ(give_up_request.get_type(), MessageType::GiveUpRequestType);
    EXPECT_EQ(give_up_request.get_game_id(), "game_id");
    EXPECT_EQ(give_up_request.get_player_id(), "player_id");
}

TEST(GiveUpRequest, To_json) {
    json j = HelperFunctions::load_json_from_file(
        "../json_examples/requests/give_up_request.json");

    GiveUpRequest give_up_request(j);

    EXPECT_EQ(give_up_request.to_json(), j);
}