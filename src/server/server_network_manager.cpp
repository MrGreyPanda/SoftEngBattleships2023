
#include "server_network_manager.h"

#include <thread>

#include "../common/network/default.conf"
#include "request_handler.h"

ServerNetworkManager::ServerNetworkManager() {
    // Create the acceptor
    const unsigned port = 1337;  // TODO move to config or get from args
    _acceptor           = sockpp::tcp_acceptor(port);

    if (!_acceptor) {
        std::cerr << "Error creating acceptor: " << _acceptor.last_error_str()
                  << std::endl;
        return;
    }

    // Start the listener loop
    start();
}

ServerNetworkManager::start() {
    // Start the listener loop
    while (true) {
        sockpp::inet_address peer;
        sockpp::tcp_socket socket = _acceptor.accept(&peer);
        std::cout << "Received connection from " << peer.to_string()
                  << std::endl;

        if (!socket) {
            std::cerr << "Error accepting connection: "
                      << socket.last_error_str() << std::endl;
            continue;
        } else {
            // TODO maybe lock and clone stuff like lama does.

            // thread to handle incoming messages
            std::thread listener(handle_socket, std::move(socket),
                                 handle_incoming_message);

            // Detach the thread so it can run in the background
            listener.detach();
        }
    }
}

void ServerNetworkManager::handle_socket(
    sockpp::tcp_socket socket,
    const std::function<void(const std::string&,
                             const sockpp::tcp_socket::addr_t&)>&
        message_handler) {
    //  handle incoming messages
    
}