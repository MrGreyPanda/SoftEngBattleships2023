#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>

#include "gtest/gtest.h"
#include "server_network_manager.h"
#include "sockpp/tcp_connector.h"

using json = nlohmann::json;

const unsigned port = 1337;
const sockpp::inet_address host_address("localhost", port);

void send_request_to_server(sockpp::tcp_connector& connector,
                            const ClientRequest& request) {
    const std::string message = request.to_string() + '\0';

    unsigned bytes_sent = connector.write(message.c_str(), message.size());
    ASSERT_TRUE(bytes_sent == message.size());
}

ServerResponse recieve_response_from_server(sockpp::tcp_connector& connector) {
    unsigned msg_length;
    char msg_buffer[512];

    if ((msg_length = connector.read(msg_buffer, sizeof(msg_buffer))) > 0) {
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

TEST(BackendIntegrationTest, JoinServerAndSendReady) {
    std::thread server_thread(ServerNetworkManager::start, port);
    server_thread.detach();

    // wait for server to start
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    sockpp::tcp_connector connector;
    bool connection_success = connector.connect(host_address);
    EXPECT_TRUE(connection_success);

    if (connection_success) {
        ClientRequest join_request(ClientRequestType::Join);
        send_request_to_server(connector, join_request);

        try {
            const ServerResponse join_response =
                recieve_response_from_server(connector);

            // check if the response is a join response
            EXPECT_TRUE(join_response.get_type() ==
                        ServerResponseType::RequestResponse);
            EXPECT_TRUE(join_response.get_request_type() ==
                        ClientRequestType::Join);

            const std::string game_id   = join_response.get_game_id();
            const std::string player_id = join_response.get_player_id();
            EXPECT_TRUE(!game_id.empty());
            EXPECT_TRUE(!player_id.empty());

            // send ready request
            ClientRequest ready_request(ClientRequestType::Ready, game_id,
                                        player_id);
            send_request_to_server(connector, ready_request);

            const ServerResponse ready_response =
                recieve_response_from_server(connector);

            // check if the response is a ready response
            EXPECT_TRUE(ready_response.get_type() ==
                        ServerResponseType::RequestResponse);
            EXPECT_TRUE(ready_response.get_request_type() ==
                        ClientRequestType::Ready);
            EXPECT_TRUE(ready_response.get_game_id() == game_id);
            EXPECT_TRUE(ready_response.get_player_id() == player_id);

        } catch (const std::exception& e) {
            FAIL() << "Caught exception: " << e.what();
        }
    }

    ServerNetworkManager::stop();
}