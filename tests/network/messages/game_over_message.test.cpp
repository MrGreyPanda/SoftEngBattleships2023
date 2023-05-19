#include "game_over_message.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(GameOverMessageTest, JSONConstructor) {
    json j = HelperFunctions::load_json_from_file(
        "../json_examples/messages/game_over_message.json");

    GameOverMessage game_over_message(j);

    EXPECT_EQ(game_over_message.get_type(), MessageType::GameOverMessageType);
    EXPECT_EQ(game_over_message.get_game_id(), j.at("game_id"));
    EXPECT_EQ(game_over_message.get_player_id(), j.at("player_id"));
    EXPECT_EQ(game_over_message.get_ship_data(), j.at("ships"));
    EXPECT_TRUE(game_over_message.has_won());
}

TEST(GameOverMessageTest, Constructor) {
    std::string game_id               = "prep_req_test_game_id";
    std::string player_id             = "prep_req_test_player_id";
    std::array<ShipData, 5> ship_data = {
        ShipData(ShipCategory::Destroyer, false, 0, 5),
        ShipData(ShipCategory::Submarine, true, 6, 8),
        ShipData(ShipCategory::Cruiser, true, 7, 6),
        ShipData(ShipCategory::Battleship, true, 6, 0),
        ShipData(ShipCategory::Carrier, false, 4, 2),
    };
    GameOverMessage game_over_message(game_id, player_id, false, ship_data);

    EXPECT_EQ(game_over_message.get_type(), MessageType::GameOverMessageType);
    EXPECT_EQ(game_over_message.get_game_id(), game_id);
    EXPECT_EQ(game_over_message.get_player_id(), player_id);
    EXPECT_EQ(game_over_message.get_ship_data(), ship_data);
    EXPECT_FALSE(game_over_message.has_won());
}

TEST(GameOverMessageTest, to_json) {
    json j = HelperFunctions::load_json_from_file(
        "../json_examples/messages/game_over_message.json");

    GameOverMessage game_over_message(j);

    json j2 = game_over_message.to_json();

    EXPECT_EQ(j, j2);
}