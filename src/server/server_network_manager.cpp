
#include "include/server_network_manager.h"

#include <thread>

// #include "../common/network/default.conf"
// #include "request_handler.h"

// Declare the static acceptor variable to allocate it as a static variable
sockpp::tcp_acceptor ServerNetworkManager::_acceptor;

ServerNetworkManager::ServerNetworkManager(unsigned port = 1337) {
    // Create the acceptor
    _acceptor = sockpp::tcp_acceptor(port);

    if (!_acceptor) {
        std::cerr << "[ServerNetworkManager] Error creating acceptor: "
                  << _acceptor.last_error_str() << std::endl;
        return;
    }

    // Start the listener loop
    std::cout << "[ServerNetworkManager] Listening on port " << port
              << std::endl;
    _start();
}

void ServerNetworkManager::broadcast(const std::string& message) {
    // TODO
}

void ServerNetworkManager::player_left(const std::string& player_id) {
    // TODO
}

void ServerNetworkManager::_start() {
    // Start the listener loop

    while (true) {
        sockpp::inet_address peer_address;
        sockpp::tcp_socket socket = _acceptor.accept(&peer_address);
        std::cout << "[ServerNetworkManager] Received connection from "
                  << peer_address.to_string() << std::endl;

        if (!socket) {
            std::cerr << "[ServerNetworkManager] Error accepting connection: "
                      << socket.last_error_str() << std::endl;
            continue;
        } else {
            // the received conncection is valid
            // try and listen to messages from this connection

            // TODO maybe add to addres to socket map like lama does

            // thread to handle incoming messages
            std::thread listener(_handle_socket, std::move(socket));

            // Detach the thread so it can run in the background
            listener.detach();
        }
    }
}

void ServerNetworkManager::_handle_socket(sockpp::tcp_socket socket) {
    //  handle incoming messages
}

void ServerNetworkManager::_handle_incoming_message(
    const std::string& message) {
    // TODO
}

void ServerNetworkManager::_send_message_to_player(
    const std::string& message, const std::string& player_id) {
    // TODO
}