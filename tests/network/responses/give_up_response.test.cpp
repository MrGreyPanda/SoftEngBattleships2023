#include "give_up_response.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(GiveUpResponse, JSONConstructor) {
    json j = HelperFunctions::load_json_from_file(
        "../json_examples/responses/give_up_response.json");

    GiveUpResponse give_up_response(j);
    EXPECT_EQ(give_up_response.get_type(), MessageType::GiveUpResponseType);
    EXPECT_EQ(give_up_response.get_game_id(), "game_id");
    EXPECT_EQ(give_up_response.get_player_id(), "player_id");
}

TEST(GiveUpResponse, Constructor) {
    GiveUpResponse give_up_response("game_id", "player_id");
    EXPECT_EQ(give_up_response.get_type(), MessageType::GiveUpResponseType);
    EXPECT_EQ(give_up_response.get_game_id(), "game_id");
    EXPECT_EQ(give_up_response.get_player_id(), "player_id");
}

TEST(GiveUpResponse, To_json) {
    json j = HelperFunctions::load_json_from_file(
        "../json_examples/responses/give_up_response.json");

    GiveUpResponse give_up_response(j);

    EXPECT_EQ(give_up_response.to_json(), j);
}
