#include "prepared_response.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(PreparedResponseTest, JSONConstructor) {
    json prepared_response_json = HelperFunctions::load_json_from_file(
        "../json_examples/responses/prepared_response.json");

    PreparedResponse prepared_response_from_json(prepared_response_json);

    EXPECT_EQ(prepared_response_from_json.get_type(),
              MessageType::PreparedResponseType);
    EXPECT_EQ(prepared_response_from_json.get_game_id(),
              prepared_response_json.at("game_id").get<std::string>());
    EXPECT_EQ(prepared_response_from_json.get_player_id(),
              prepared_response_json.at("player_id").get<std::string>());
    EXPECT_EQ(prepared_response_from_json.get_ship_data(),
              prepared_response_json.at("ships"));
    EXPECT_TRUE(prepared_response_from_json.is_valid());
    EXPECT_EQ(prepared_response_from_json.get_error(),
              prepared_response_json.at("error").get<std::string>());
}

TEST(PreparedResponseTest, NoErrorConstructor) {
    std::string game_id               = "test_prep_res_game_id";
    std::string player_id             = "test_prep_res_player_id";
    std::array<ShipData, 5> ship_data = {
        ShipData(ShipCategory::Destroyer, false, 0, 5),
        ShipData(ShipCategory::Submarine, true, 6, 8),
        ShipData(ShipCategory::Cruiser, true, 7, 6),
        ShipData(ShipCategory::Battleship, true, 6, 0),
        ShipData(ShipCategory::Carrier, false, 4, 2),
    };
    PreparedResponse prepared_response(game_id, player_id, ship_data, true);

    EXPECT_EQ(prepared_response.get_type(), MessageType::PreparedResponseType);
    EXPECT_EQ(prepared_response.get_game_id(), game_id);
    EXPECT_EQ(prepared_response.get_player_id(), player_id);
    EXPECT_EQ(prepared_response.get_ship_data(), ship_data);
    EXPECT_TRUE(prepared_response.is_valid());
    EXPECT_TRUE(prepared_response.get_error().empty());
}

TEST(PreparedResponseTest, ErrorConstructor) {
    std::string game_id               = "test_prep_res_game_id";
    std::string player_id             = "test_prep_res_player_id";
    std::array<ShipData, 5> ship_data = {
        ShipData(ShipCategory::Destroyer, false, 0, 5),
        ShipData(ShipCategory::Submarine, true, 6, 8),
        ShipData(ShipCategory::Cruiser, true, 7, 6),
        ShipData(ShipCategory::Battleship, true, 6, 0),
        ShipData(ShipCategory::Carrier, false, 4, 2),
    };
    std::string error = "test_prep_res_error";
    PreparedResponse prepared_response(game_id, player_id, ship_data, false,
                                       error);

    EXPECT_EQ(prepared_response.get_type(), MessageType::PreparedResponseType);
    EXPECT_EQ(prepared_response.get_game_id(), game_id);
    EXPECT_EQ(prepared_response.get_player_id(), player_id);
    EXPECT_EQ(prepared_response.get_ship_data(), ship_data);
    EXPECT_FALSE(prepared_response.is_valid());
    EXPECT_EQ(prepared_response.get_error(), error);
}