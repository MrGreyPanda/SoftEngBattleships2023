#include "gave_up_message.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(GaveUpMessage, JSONConstructor) {
    json j = HelperFunctions::load_json_from_file(
        "../json_examples/messages/gave_up_message.json");

    GaveUpMessage gave_up_message(j);
    EXPECT_EQ(gave_up_message.get_type(), MessageType::GaveUpMessageType);
    EXPECT_EQ(gave_up_message.get_game_id(), j.at("game_id"));
    EXPECT_EQ(gave_up_message.get_player_id(), j.at("player_id"));
}

TEST(GaveUpMessage, Constructor) {
    GaveUpMessage gave_up_message("game_id", "player_id");
    EXPECT_EQ(gave_up_message.get_type(), MessageType::GaveUpMessageType);
    EXPECT_EQ(gave_up_message.get_game_id(), "game_id");
    EXPECT_EQ(gave_up_message.get_player_id(), "player_id");
}

TEST(GaveUpMessage, To_json) {
    json j = HelperFunctions::load_json_from_file(
        "../json_examples/messages/gave_up_message.json");

    GaveUpMessage gave_up_message(j);

    EXPECT_EQ(gave_up_message.to_json(), j);
}
