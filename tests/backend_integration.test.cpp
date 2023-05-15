#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>

#include "client_join_request.h"
#include "client_ready_request.h"
#include "gtest/gtest.h"
#include "server_network_manager.h"
#include "sockpp/tcp_connector.h"

using json = nlohmann::json;

const unsigned port = 1337;
const sockpp::inet_address host_address("localhost", port);

sockpp::tcp_connector connector;

std::string game_id;
std::string player_id;

void send_request_to_server(const std::string& request_string) {
    const std::string message = request_string + '\0';

    unsigned bytes_sent = connector.write(message.c_str(), message.size());
    ASSERT_TRUE(bytes_sent == message.size());
}

ServerResponse recieve_response_from_server() {
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

TEST(BackendIntegrationTest, StartServer) {
    std::thread server_thread(ServerNetworkManager::start, port);
    server_thread.detach();

    // wait for server to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(BackendIntegrationTest, Connect) {
    bool connection_success = connector.connect(host_address);
    EXPECT_TRUE(connection_success);
}

TEST(BackendIntegrationTest, Join) {
    ClientJoinRequest join_request;
    send_request_to_server(join_request.to_string());

    try {
        const ServerResponse join_response = recieve_response_from_server();

        // check if the response is a join response
        EXPECT_TRUE(join_response.get_type() ==
                    ServerResponseType::RequestResponse);
        EXPECT_TRUE(join_response.get_request_type() ==
                    ClientRequestType::Join);

        game_id = join_response.get_game_id();
        EXPECT_TRUE(!game_id.empty());

        player_id = join_response.get_player_id();
        EXPECT_TRUE(!player_id.empty());

    } catch (const std::exception& e) {
        FAIL() << "Caught exception: " << e.what();
    }
}

TEST(BackendIntegrationTest, Ready) {
    // send ready request
    ClientReadyRequest ready_request(game_id, player_id);
    send_request_to_server(ready_request.to_string());

    const ServerResponse ready_response = recieve_response_from_server();

    // check if the response is a ready response
    EXPECT_TRUE(ready_response.get_type() ==
                ServerResponseType::RequestResponse);
    EXPECT_TRUE(ready_response.get_request_type() == ClientRequestType::Ready);
    EXPECT_TRUE(ready_response.get_game_id() == game_id);
    EXPECT_TRUE(ready_response.get_player_id() == player_id);
}

TEST(BackendIntegrationTest, Preparation) {}

TEST(BackendIntegrationTest, Shoot) {}

TEST(BackendIntegrationTest, GiveUp) {}

TEST(BackendIntegrationTest, DisconnectAndShutdownServer) {
    connector.close();

    EXPECT_TRUE(!connector.is_open());

    ServerNetworkManager::stop();
}