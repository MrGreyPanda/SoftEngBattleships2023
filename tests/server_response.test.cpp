#include "server_response.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "gtest/gtest.h"

using json = nlohmann::json;

TEST(ServerResponseTest, CreateServerJoinRequestFromJSON) {
    std::ifstream file("../json_examples/responses/join_response.json");

    // load json from file
    json json_data = json::parse(file);

    ServerResponse *server_response_ptr;
    try {
        server_response_ptr = new ServerResponse(json_data);
    } catch (const std::exception &e) {
        std::cout << "Error creating server response object: " << e.what()
                  << std::endl;
        FAIL();
    }
    EXPECT_EQ(server_response_ptr->get_type(),
              ServerResponseType::RequestResponse);
    EXPECT_EQ(server_response_ptr->get_request_type(),
              ClientRequestType::Join);
    EXPECT_EQ(server_response_ptr->get_game_id(),
              json_data["game_id"].get<std::string>());
    EXPECT_EQ(server_response_ptr->get_player_id(),
              json_data["player_id"].get<std::string>());
              
    delete server_response_ptr;
    server_response_ptr = nullptr;
}

TEST(ServerResponseTest, GetServerRequestTypeFromMessageTypeString) {
    ServerResponseType req_res_type =
        ServerResponse::get_server_request_type_from_message_type_string(
            "response");
    EXPECT_EQ(req_res_type, ServerResponseType::RequestResponse);

    ServerResponseType full_res_type =
        ServerResponse::get_server_request_type_from_message_type_string(
            "full_state");
    EXPECT_EQ(full_res_type, ServerResponseType::FullStateMessage);
}