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
              ClientRequestType::ClientJoinRequest);
    EXPECT_EQ(server_response_ptr->get_game_id(),
              json_data["game_id"].get<std::string>());
    EXPECT_EQ(server_response_ptr->get_player_id(),
              json_data["player_id"].get<std::string>());
}

// TEST(ServerResponse)