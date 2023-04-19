
#include "server_network_manager.h"

#include "../common/network/default.conf"
#include "request_handler.h"

ServerNetworkManager::ServerNetworkManager() {
    // Create the acceptor
    _acceptor = sockpp::tcp_acceptor(DEFAULT_PORT);

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
            // TODO create a listener thread and transfer the new socket to it
            // and handle incoming messages
            std::thread listener(handle_thread, std::move(socket),
                                 handle_incoming_message);
        }
    }
}