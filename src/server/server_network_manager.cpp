

#include "server_network_manager.h"

#include <nlohmann/json.hpp>
#include <thread>

#include "request_handler.h"

using json = nlohmann::json;

// Declare the static variables to allocate them

sockpp::tcp_acceptor ServerNetworkManager::acceptor_;

std::shared_mutex ServerNetworkManager::player_addr_mutex_;

std::unordered_map<std::string, std::string>
    ServerNetworkManager::player_addresses_;

std::shared_mutex ServerNetworkManager::sockets_mutex_;

std::unordered_map<std::string, sockpp::tcp_socket>
    ServerNetworkManager::sockets_;

ServerNetworkManager::ServerNetworkManager(unsigned port) {
    // Create the acceptor
    acceptor_ = sockpp::tcp_acceptor(port);

    if (!acceptor_) {
        std::cerr << "[ServerNetworkManager] Error creating acceptor: "
                  << acceptor_.last_error_str() << std::endl;
        return;
    }

    // Start the listener loop
    std::cout << "[ServerNetworkManager] Listening on port " << port
              << std::endl;
    start_();
}

void ServerNetworkManager::send_response(const ServerResponse& response,
                                         const std::string& player_id) {
    // Get the IP address of the player
    // TODO

    // Get the socket for the IP address
    // TODO

    // Send the response
    // socket.write(response_str.c_str(), response_str.length());
}

void ServerNetworkManager::start_() {
    // Start the listener loop

    while (true) {
        sockpp::inet_address peer_address;
        sockpp::tcp_socket socket = acceptor_.accept(&peer_address);
        std::cout << "[ServerNetworkManager] Received connection from "
                  << peer_address.to_string() << std::endl;

        if (!socket) {
            std::cerr << "[ServerNetworkManager] Error accepting connection: "
                      << socket.last_error_str() << std::endl;
            continue;
        } else {
            // the received conncection is valid
            // try and listen to messages from this connection

            // create thread to handle incoming messages
            std::thread listener(handle_socket_, std::move(socket));

            // Detach the thread so it can run in the background
            listener.detach();
        }
    }
}

void ServerNetworkManager::handle_socket_(sockpp::tcp_socket socket) {
    //  handle incoming messages
    ssize_t msg_length;
    char msg_buffer[512];
    const sockpp::inet_address peer_address = socket.peer_address();

    sockets_mutex_.lock();
    sockets_.emplace(peer_address.to_string(), std::move(socket.clone()));
    sockets_mutex_.unlock();

    // TODO handle messages larger than 512 bytes
    while ((msg_length = socket.read(msg_buffer, sizeof(msg_buffer))) > 0) {
        try {
            std::stringstream ss;
            ss.write(msg_buffer, msg_length);
            std::string line;

            while (std::getline(ss, line, '\0')) {
                std::string message = line;
                handle_incoming_message_(message, peer_address);
            }
        } catch (std::exception& err) {
            std::cerr
                << "[ServerNetworkManager] Error handling socket message: "
                << err.what() << std::endl;
        }
    }

    std::cout << "[ServerNetworkManager] Closing connection to "
              << socket.peer_address() << std::endl;

    // Delete the socket from the map
    sockets_mutex_.lock();
    sockets_.erase(peer_address.to_string());
    sockets_mutex_.unlock();

    std::cout << "[ServerNetworkManager] (Debug) Removed the socket for peer "
              << socket.peer_address() << std::endl;
}

void ServerNetworkManager::handle_incoming_message_(
    const std::string& message, const sockpp::inet_address& peer_address) {
    // try to parse the message as JSON and create a client request object
    json data;
    try {
        data = json::parse(message);
    } catch (json::parse_error& e) {
        std::cout << "[ServerNetworkManager] JSON parse error: " << e.what()
                  << std::endl;
        std::cout << "[ServerNetworkManager] Message was: '" << message << "'"
                  << std::endl;

        // create error response
        const ServerResponse error_response(
            ServerResponseType::RequestResponse, "Error: Invalid JSON");

        send_response(error_response, peer_address.to_string());
        return;
    }

    ClientRequest* client_request;
    try {
        client_request = new ClientRequest(data);
    } catch (std::exception& e) {
        std::cout << "[ServerNetworkManager] Message is not a valid "
                     "ClientRequest.\n"
                     " Error from ClientRequest constructor: "
                  << e.what()
                  << "\nClientRequest was not created and reading the message "
                     "aborted!"
                  << std::endl;

        const ServerResponse response(
            ServerResponseType::RequestResponse,
            "Error: Message is not a valid ClientRequest");

        send_response(response, peer_address.to_string());
        return;
    }

    // Create a player id for this connection if it is a join request
    // Also add the player to a game
    if (client_request->get_type() == ClientRequestType::ClientJoinRequest) {
        Player* player_ptr =
            RequestHandler::handle_join_request(*client_request);

        if (player_ptr != nullptr) {
            player_addr_mutex_.lock();
            // TODO check if player_ptr has ID maybe?
            player_addresses_.emplace(player_ptr->get_id(),
                                      peer_address.to_string());
            player_addr_mutex_.unlock();
        }
    }

    // check if this is a message from a known player
    std::string player_id = client_request->get_player_id();

    if (player_addresses_.find(player_id) == player_addresses_.end()) {
        // This is not a message from a known player
        std::cout << "[ServerNetworkManager] Error: Player with ID '"
                  << player_id << "' is not a known player of this game."
                  << std::endl;

        // create error response
        const ServerResponse response(
            ServerResponseType::RequestResponse, client_request->get_type(),
            "", player_id, "Error: Player is not a known player of this game");

        send_response(response, peer_address.to_string());
        return;
    }

    RequestHandler::handle_request(*client_request);
}
