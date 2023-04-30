#include "../network/requests/client_request.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "gtest/gtest.h"

using json = nlohmann::json;

TEST(ClientRequestTest, CreateClientJoinRequestFromJSON) {
    std::ifstream file(
        "../src/common/network/requests/examples/join_request.json");

    // load json from file
    json json_data = json::parse(file);

    ClientRequest *client_request_ptr;
    try {
        client_request_ptr = new ClientRequest(json_data);
    } catch (const std::exception &e) {
        std::cout << "Error creating client request object: " << e.what()
                  << std::endl;
        FAIL();
    }
    EXPECT_EQ(client_request_ptr->get_type(),
              ClientRequestType::ClientJoinRequest);
    EXPECT_EQ(client_request_ptr->get_game_id(), "");
    EXPECT_EQ(client_request_ptr->get_player_id(), "");
}

TEST(ClientRequestTest, CreateClientReadyRequestFromJSON) {
    std::ifstream file(
        "../src/common/network/requests/examples/ready_request.json");

    // load json from file
    json json_data = json::parse(file);

    ClientRequest *client_request_ptr;
    try {
        client_request_ptr = new ClientRequest(json_data);
    } catch (const std::exception &e) {
        std::cout << "Error creating client request object: " << e.what()
                  << std::endl;
        FAIL();
    }

    EXPECT_EQ(client_request_ptr->get_type(),
              ClientRequestType::ClientReadyRequest);
    EXPECT_EQ(client_request_ptr->get_game_id(), json_data["game_id"]);
    EXPECT_EQ(client_request_ptr->get_player_id(), json_data["player_id"]);
}

TEST(ClientRequestTest, GetClientRequestTypeFromMesssageTypeString) {
    EXPECT_EQ(ClientRequest::get_client_request_type_from_message_type_string(
                  "join"),
              ClientRequestType::ClientJoinRequest);
    EXPECT_EQ(ClientRequest::get_client_request_type_from_message_type_string(
                  "ready"),
              ClientRequestType::ClientReadyRequest);
    EXPECT_EQ(ClientRequest::get_client_request_type_from_message_type_string(
                  "prepared"),
              ClientRequestType::ClientPreparedRequest);
    EXPECT_EQ(ClientRequest::get_client_request_type_from_message_type_string(
                  "shoot"),
              ClientRequestType::ClientShootRequest);
    EXPECT_EQ(ClientRequest::get_client_request_type_from_message_type_string(
                  "give_up"),
              ClientRequestType::ClientGiveUpRequest);

    // unknown message type string
    EXPECT_EQ(ClientRequest::get_client_request_type_from_message_type_string(
                  "whatever"),
              ClientRequestType::ClientUnknownRequest);
}