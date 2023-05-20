#include "prepared_message.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(PreparedMessage, JSONConstructor) {
    json prepared_msg_json = HelperFunctions::load_json_from_file(
        "../json_examples/messages/prepared_message.json");

    PreparedMessage prepared_message(prepared_msg_json);

    EXPECT_EQ(prepared_message.get_type(), MessageType::PreparedMessageType);
    EXPECT_EQ(prepared_message.get_game_id(),
              prepared_msg_json.at("game_id").get<std::string>());
    EXPECT_EQ(prepared_message.get_player_id(),
              prepared_msg_json.at("player_id").get<std::string>());
}

TEST(PreparedMessage, Constructor) {
    std::string game_id   = "prep_msg_test_game_id";
    std::string player_id = "prep_msg_test_player_id";
    PreparedMessage prepared_message(game_id, player_id);

    EXPECT_EQ(prepared_message.get_type(), MessageType::PreparedMessageType);
    EXPECT_EQ(prepared_message.get_game_id(), game_id);
    EXPECT_EQ(prepared_message.get_player_id(), player_id);
}