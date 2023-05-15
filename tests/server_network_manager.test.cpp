#include "server_network_manager.h"

#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>

#include "gtest/gtest.h"
#include "sockpp/tcp_connector.h"

using json = nlohmann::json;

const unsigned port = 1337;
const sockpp::inet_address host_address("localhost", port);

void send_message_to_server(sockpp::tcp_connector& connector,
                            const ClientRequest& request) {
    const std::string message = request.to_string() + '\0';

    unsigned bytes_sent = connector.write(message.c_str(), message.size());
    ASSERT_TRUE(bytes_sent == message.size());
}

ServerResponse recieve_response_from_server(sockpp::tcp_connector& connector) {
    unsigned msg_length;
    char msg_buffer[512];

    while ((msg_length = connector.read(msg_buffer, sizeof(msg_buffer))) > 0) {
        // parse the message
        std::stringstream str_stream;
        str_stream.write(msg_buffer, msg_length);
        std::string line;

        if (std::getline(str_stream, line, '\0')) {
            const json message_json = json::parse(line);
            const ServerResponse response(message_json);

            return response;
        } else {
            throw std::runtime_error("Failed to parse message");
        }
    }
    throw std::runtime_error("Failed to recieve message");
}

TEST(ServerNetworkManagerTest, HandleNewConnection) {
    std::thread server_thread(ServerNetworkManager::start, port);
    server_thread.detach();
    sockpp::tcp_connector connector = sockpp::tcp_connector();

    // wait for the server to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // test if the server is running on the correct port
    // TODO

    const bool connection_success = connector.connect(host_address);
    EXPECT_TRUE(connection_success);

    // stop the server network manager
    ServerNetworkManager::stop();
}

TEST(ServerNetworkManagerTest, HandleJoinRequest) {
    std::thread server_thread(ServerNetworkManager::start, port);
    server_thread.detach();

    // wait for server to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    sockpp::tcp_connector connector;
    bool connection_success = connector.connect(host_address);
    EXPECT_TRUE(connection_success);

    if (connection_success) {
        ClientRequest join_request(ClientRequestType::ClientJoinRequest);
        send_message_to_server(connector, join_request);

        try {
            const ServerResponse response =
                recieve_response_from_server(connector);

            // check if the response is a join response
            EXPECT_TRUE(response.get_type() ==
                        ServerResponseType::RequestResponse);
            EXPECT_TRUE(response.get_request_type() ==
                        ClientRequestType::ClientJoinRequest);

            const std::string game_id   = response.get_game_id();
            const std::string player_id = response.get_player_id();
            EXPECT_TRUE(!game_id.empty());
            EXPECT_TRUE(!player_id.empty());

        } catch (const std::exception& e) {
            FAIL() << "Caught exception: " << e.what();
        }
    }

    ServerNetworkManager::stop();
}

TEST(ServerNetworkManagerTest, HandlePlayerIdMismatch) {}