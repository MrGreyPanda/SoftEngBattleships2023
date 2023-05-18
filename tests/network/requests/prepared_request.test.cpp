
#include "prepared_request.h"

#include "gtest/gtest.h"
#include "helper_functions.h"

TEST(PreparedRequestTest, JSONConstructor) {
    json prepared_req_json = HelperFunctions::load_json_from_file(
        "../json_examples/requests/prepared_request.json");

    PreparedRequest prepared_request(prepared_req_json);

    EXPECT_EQ(prepared_request.get_type(), MessageType::PreparedRequestType);
    EXPECT_EQ(prepared_request.get_game_id(),
              prepared_req_json.at("game_id").get<std::string>());
    EXPECT_EQ(prepared_request.get_player_id(),
              prepared_req_json.at("player_id").get<std::string>());

    std::vector<ShipData> ship_data =
        prepared_req_json.at("ships").get<std::vector<ShipData>>();
    EXPECT_EQ(prepared_request.get_ship_data(), ship_data);
}

TEST(PreparedRequestTest, Constructor) {
    std::string game_id             = "prep_req_test_game_id";
    std::string player_id           = "prep_req_test_player_id";
    std::vector<ShipData> ship_data = {
        ShipData(ShipCategory::Destroyer, false, 0, 5),
        ShipData(ShipCategory::Submarine, true, 6, 8),
        ShipData(ShipCategory::Cruiser, true, 7, 6),
        ShipData(ShipCategory::Battleship, true, 6, 0),
        ShipData(ShipCategory::Carrier, false, 4, 2),
    };
    PreparedRequest prepared_request(game_id, player_id, ship_data);

    EXPECT_EQ(prepared_request.get_type(), MessageType::PreparedRequestType);
    EXPECT_EQ(prepared_request.get_game_id(), game_id);
    EXPECT_EQ(prepared_request.get_player_id(), player_id);
    EXPECT_EQ(prepared_request.get_ship_data(), ship_data);
}

TEST(PreparedRequestTest, to_json) {
    json prepared_req_json = HelperFunctions::load_json_from_file(
        "../json_examples/requests/prepared_request.json");

    PreparedRequest prepared_request(prepared_req_json);

    json prepared_req_json_2 = prepared_request.to_json();

    EXPECT_EQ(prepared_req_json, prepared_req_json_2);
}

TEST(PreparedRequestTest, to_string) {
    json prepared_req_json = HelperFunctions::load_json_from_file(
        "../json_examples/requests/prepared_request.json");

    PreparedRequest prepared_request(prepared_req_json);

    std::string prepared_req_string = prepared_request.to_string();

    EXPECT_EQ(prepared_req_string, prepared_req_json.dump());
}