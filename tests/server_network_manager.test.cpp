#include "server_network_manager.h"

#include <thread>

#include "gtest/gtest.h"
#include "sockpp/tcp_connector.h"

const unsigned port = 1337;
const sockpp::inet_address host_address("localhost", port);

TEST(ServerNetworkManagerTest, HandleNewConnection) {
    std::thread server_thread(ServerNetworkManager::start, port);
    server_thread.detach();
    sockpp::tcp_connector connector = sockpp::tcp_connector();

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
        const std::string message = join_request.to_string() + '\0';

        unsigned bytes_sent = connector.write(message.c_str(), message.size());
        ASSERT_TRUE(bytes_sent == message.size());
    }

    ServerNetworkManager::stop();
}

TEST(ServerNetworkManagerTest, HandlePlayerIdMismatch) {}