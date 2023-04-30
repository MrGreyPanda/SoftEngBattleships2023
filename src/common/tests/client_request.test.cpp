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

    const ClientRequest client_request = ClientRequest(json_data);
    EXPECT_EQ(client_request.get_type(), ClientJoinRequest);
}