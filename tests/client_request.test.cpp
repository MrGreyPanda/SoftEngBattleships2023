#include "client_request.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <tuple>

#include "gtest/gtest.h"

using json = nlohmann::json;

std::tuple<json, ClientRequest *> _parse_client_join_request() {
    try {
        // load json from file
        std::ifstream file("../json_examples/requests/join_request.json");

        json json_data = json::parse(file);

        return {json_data, new ClientRequest(json_data)};
    } catch (const std::exception &e) {
        std::cout << "Error creating client request object: " << e.what()
                  << std::endl;
        return {json(), nullptr};
    }
}

std::tuple<json, ClientRequest *> _parse_client_ready_request() {
    try {
        std::ifstream file("../json_examples/requests/ready_request.json");

        // load json from file
        json json_data = json::parse(file);

        return {json_data, new ClientRequest(json_data)};
    } catch (const std::exception &e) {
        std::cout << "Error creating client request object: " << e.what()
                  << std::endl;
        return {json(), nullptr};
    }
}

TEST(ClientRequestTest, CreateClientJoinRequestFromJSON) {
    auto parsed_info_tuple            = _parse_client_join_request();
    ClientRequest *client_request_ptr = std::get<1>(parsed_info_tuple);

    if (client_request_ptr == nullptr) {
        FAIL();
    }

    EXPECT_EQ(client_request_ptr->get_type(),
              ClientRequestType::ClientJoinRequest);
    EXPECT_EQ(client_request_ptr->get_game_id(), "");
    EXPECT_EQ(client_request_ptr->get_player_id(), "");

    delete std::get<1>(parsed_info_tuple);
}

TEST(ClientRequestTest, CreateClientReadyRequestFromJSON) {
    auto parsed_info_tuple            = _parse_client_ready_request();
    json json_data                    = std::get<0>(parsed_info_tuple);
    ClientRequest *client_request_ptr = std::get<1>(parsed_info_tuple);

    if (client_request_ptr == nullptr) {
        FAIL();
    }

    EXPECT_EQ(client_request_ptr->get_type(),
              ClientRequestType::ClientReadyRequest);
    EXPECT_EQ(client_request_ptr->get_game_id(),
              json_data["game_id"].get<std::string>());
    EXPECT_EQ(client_request_ptr->get_player_id(),
              json_data["player_id"].get<std::string>());
              
    delete std::get<1>(parsed_info_tuple);
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

TEST(ClientRequestTest, ClientRequestToJSON) {
    auto parsed_info_tuple            = _parse_client_ready_request();
    json json_data                    = std::get<0>(parsed_info_tuple);
    ClientRequest *client_request_ptr = std::get<1>(parsed_info_tuple);

    if (client_request_ptr == nullptr) {
        FAIL();
    }

    EXPECT_EQ(client_request_ptr->to_json().dump(), json_data.dump());

    delete std::get<1>(parsed_info_tuple);
}

TEST(ClientRequestTest, ClientRequestToString) {
    auto parsed_info_tuple            = _parse_client_ready_request();
    json json_data                    = std::get<0>(parsed_info_tuple);
    ClientRequest *client_request_ptr = std::get<1>(parsed_info_tuple);

    if (client_request_ptr == nullptr) {
        FAIL();
    }

    EXPECT_EQ(client_request_ptr->to_string(), json_data.dump());

    delete std::get<1>(parsed_info_tuple);
}