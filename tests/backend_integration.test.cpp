#include <future>
#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>

#include "client_join_request.h"
#include "client_prepared_request.h"
#include "client_ready_request.h"
#include "gtest/gtest.h"
#include "server_network_manager.h"
#include "ship.h"
#include "sockpp/tcp_connector.h"

using json = nlohmann::json;

const unsigned port = 1337;
const sockpp::inet_address host_address("localhost", port);

sockpp::tcp_connector connector_1;
sockpp::tcp_connector connector_2;

std::string game_id_1;
std::string game_id_2;

std::string player_id_1;
std::string player_id_2;

std::vector<Ship> ships_1;
std::vector<Ship> ships_2;

void send_request_to_server(sockpp::tcp_connector& connector,
                            const std::string& request_string) {
    const std::string message = request_string + '\0';

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

TEST(BackendIntegrationTest, StartServer) {
    std::thread server_thread(ServerNetworkManager::start, port);
    server_thread.detach();

    // wait for server to start
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(BackendIntegrationTest, Connect) {
    // Player 1
    bool connection_1_success = connector_1.connect(host_address);
    EXPECT_TRUE(connection_1_success);

    // Player 2
    bool connection_2_success = connector_2.connect(host_address);
    EXPECT_TRUE(connection_2_success);
}

TEST(BackendIntegrationTest, Join) {
    ClientJoinRequest join_request;

    // Launch async tasks for sending requests and receiving responses
    auto task1 = std::async(std::launch::async, [&]() {
        send_request_to_server(connector_1, join_request.to_string());
        return recieve_response_from_server(connector_1);
    });
    auto task2 = std::async(std::launch::async, [&]() {
        send_request_to_server(connector_2, join_request.to_string());
        return recieve_response_from_server(connector_2);
    });

    try {
        // Get the results from the async tasks
        const ServerResponse join_response_1 = task1.get();

        // for player 1
        EXPECT_EQ(join_response_1.get_type(),
                  ServerResponseType::RequestResponse);
        EXPECT_EQ(join_response_1.get_request_type(), ClientRequestType::Join);

        game_id_1 = join_response_1.get_game_id();
        EXPECT_FALSE(game_id_1.empty());

        player_id_1 = join_response_1.get_player_id();
        EXPECT_FALSE(player_id_1.empty());

        // for player 2
        const ServerResponse join_response_2 = task2.get();
        EXPECT_EQ(join_response_2.get_type(),
                  ServerResponseType::RequestResponse);
        EXPECT_EQ(join_response_2.get_request_type(), ClientRequestType::Join);

        game_id_2 = join_response_2.get_game_id();
        EXPECT_FALSE(game_id_2.empty());

        player_id_2 = join_response_2.get_player_id();
        EXPECT_FALSE(player_id_2.empty());

    } catch (const std::exception& e) {
        FAIL() << "Caught exception: " << e.what();
    }
}

TEST(BackendIntegrationTest, Ready) {
    // send ready request player 1
    ClientReadyRequest ready_request_1(game_id_1, player_id_1);
    send_request_to_server(connector_1, ready_request_1.to_string());

    const ServerResponse ready_response_1 =
        recieve_response_from_server(connector_1);

    EXPECT_EQ(ready_response_1.get_type(),
              ServerResponseType::RequestResponse);
    EXPECT_EQ(ready_response_1.get_request_type(), ClientRequestType::Ready);
    EXPECT_EQ(ready_response_1.get_game_id(), game_id_1);
    EXPECT_EQ(ready_response_1.get_player_id(), player_id_1);

    // send ready request player 2
    ClientReadyRequest ready_request_2(game_id_2, player_id_2);
    send_request_to_server(connector_2, ready_request_2.to_string());

    const ServerResponse ready_response_2 =
        recieve_response_from_server(connector_2);

    // check if the response is a ready response
    EXPECT_EQ(ready_response_2.get_type(),
              ServerResponseType::RequestResponse);
    EXPECT_EQ(ready_response_2.get_request_type(), ClientRequestType::Ready);
    EXPECT_EQ(ready_response_2.get_game_id(), game_id_2);
    EXPECT_EQ(ready_response_2.get_player_id(), player_id_2);
}

/**
 * @brief Simulate two players having prepared their board and being ready to
 * start the game.
 */
TEST(BackendIntegrationTest, Preparation) {
    // Place ships for player 1
    std::vector<ShipData> ships_data_1 = {
        ShipData(ShipCategory::Carrier, false, 4, 2),
        ShipData(ShipCategory::Battleship, true, 6, 0),
        ShipData(ShipCategory::Cruiser, true, 7, 6),
        ShipData(ShipCategory::Submarine, true, 6, 8),
        ShipData(ShipCategory::Destroyer, false, 0, 5),
    };

    const ClientPreparedRequest preparation_request_1(game_id_1, player_id_1,
                                                      ships_data_1);

    // Place ships for player 2
    std::vector<ShipData> ships_data_2 = {
        ShipData(ShipCategory::Carrier, false, 0, 0),
        ShipData(ShipCategory::Battleship, true, 6, 9),
        ShipData(ShipCategory::Cruiser, false, 6, 1),
        ShipData(ShipCategory::Submarine, true, 4, 0),
        ShipData(ShipCategory::Destroyer, false, 5, 3),
    };

    const ClientPreparedRequest preparation_request_2(game_id_2, player_id_2,
                                                      ships_data_2);
}

TEST(BackendIntegrationTest, Shoot) {}

TEST(BackendIntegrationTest, GiveUp) {}

TEST(BackendIntegrationTest, DisconnectAndShutdownServer) {
    connector_1.close();
    connector_2.close();

    EXPECT_FALSE(connector_1.is_open());
    EXPECT_FALSE(connector_2.is_open());

    ServerNetworkManager::stop();
}