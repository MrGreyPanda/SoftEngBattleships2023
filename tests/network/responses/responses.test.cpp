#include "gtest/gtest.h"
#include "response.h"

TEST(Response, Constructor) {
    Response response(MessageType::ReadyResponseType, "test_game_id",
                      "test_player_id");
    EXPECT_EQ(response.get_type(), MessageType::ReadyResponseType);
    EXPECT_EQ(response.get_game_id(), "test_game_id");
    EXPECT_EQ(response.get_player_id(), "test_player_id");
    EXPECT_EQ(response.get_error(), "");
}

TEST(Response, ConstructorWithError) {
    Response response(MessageType::ReadyResponseType, "test_game_id",
                      "test_player_id", "test_error");
    EXPECT_EQ(response.get_type(), MessageType::ReadyResponseType);
    EXPECT_EQ(response.get_game_id(), "test_game_id");
    EXPECT_EQ(response.get_player_id(), "test_player_id");
    EXPECT_EQ(response.get_error(), "test_error");
}

TEST(Response, toJSON) {
    Response response(MessageType::ReadyResponseType, "test_game_id",
                      "test_player_id");
    EXPECT_EQ(
        response.to_json(),
        json::parse(
            "{\"game_id\":\"test_game_id\",\"player_id\":\"test_player_id\","
            "\"type\":\"ready_response\"}"));
}

TEST(Response, toJSONWithError) {
    Response response(MessageType::ReadyResponseType, "test_game_id",
                      "test_player_id", "test_error");
    EXPECT_EQ(
        response.to_json(),
        json::parse(
            "{\"error\":\"test_error\",\"game_id\":\"test_game_id\","
            "\"player_id\":\"test_player_id\",\"type\":\"ready_response\"}"));
}

TEST(Response, toString) {
    Response response(MessageType::ReadyResponseType, "test_game_id",
                      "test_player_id");
    EXPECT_EQ(response.to_string(),
              "{\"game_id\":\"test_game_id\",\"player_id\":\"test_player_id\","
              "\"type\":\"ready_response\"}");
}
