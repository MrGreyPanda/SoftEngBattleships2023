#include "base_message.h"
#include "gtest/gtest.h"
#include "message.h"

TEST(BaseMessage, JSONConstructor) {
    json j;
    j["type"] = "shot_message";
    BaseMessage m(j);
    EXPECT_EQ(m.get_type(), MessageType::ShotMessageType);
}

TEST(BaseMessage, TypeConstructor) {
    BaseMessage m(MessageType::ReadyResponseType);
    EXPECT_EQ(m.get_type(), MessageType::ReadyResponseType);
}

TEST(BaseMessage, toJSON) {
    BaseMessage m(MessageType::GaveUpMessageType);
    EXPECT_EQ(m.to_json(), json::parse("{\"type\":\"gave_up_message\"}"));
}

TEST(BaseMessage, toString) {
    BaseMessage m(MessageType::JoinRequestType);
    EXPECT_EQ(m.to_string(), "{\"type\":\"join_request\"}");
}

TEST(Message, JSONConstructor) {
    json j;
    j["type"]      = "game_over_message";
    j["game_id"]   = "test_game_id";
    j["player_id"] = "test_player_id";
    Message m(j);
    EXPECT_EQ(m.get_type(), MessageType::GameOverMessageType);
    EXPECT_EQ(m.get_game_id(), "test_game_id");
    EXPECT_EQ(m.get_player_id(), "test_player_id");
}

TEST(Message, toJSON) {
    Message m(MessageType::JoinResponseType, "test_game_id", "test_player_id");
    EXPECT_EQ(
        m.to_json(),
        json::parse(
            "{\"game_id\":\"test_game_id\",\"player_id\":\"test_player_id\","
            "\"type\":\"join_response\"}"));
}

TEST(Message, toString) {
    Message m(MessageType::JoinResponseType, "test_game_id", "test_player_id");
    EXPECT_EQ(m.to_string(),
              "{\"game_id\":\"test_game_id\",\"player_id\":\"test_player_id\","
              "\"type\":\"join_response\"}");
}