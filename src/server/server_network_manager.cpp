

#include "server_network_manager.h"

#include <nlohmann/json.hpp>
#include <thread>

#include "game_instance_manager.h"
#include "helper_functions.h"
#include "player.h"
#include "player_manager.h"

using json = nlohmann::json;

// Declare the static variables to allocate them
std::shared_mutex ServerNetworkManager::player_addr_mutex_;
sockpp::tcp_acceptor ServerNetworkManager::acceptor_;
std::unordered_map<std::string, std::string>
    ServerNetworkManager::player_addresses_;

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
                                         std::string& player_id) {
    // Get the socket for a player
    // TODO

    socket.write(response_str.c_str(), response_str.length());
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

    socket_mutex_.lock();
    sockets_.emplace(peer_address.to_string(), std::move(socket.clone()));
    socket_mutex_.unlock();

    while ((msg_length = socket.read(msg_buffer, sizeof(msg_buffer))) > 0) {
        try {
            std::string message(msg_buffer, msg_length);
            handle_incoming_message_(message, peer_address);
        } catch (std::exception& err) {
            std::cerr
                << "[ServerNetworkManager] Error handling socket message: "
                << err.what() << std::endl;
        }
    }

    std::cout << "[ServerNetworkManager] Closing connection to "
              << socket.peer_address() << std::endl;

    // Delete the socket from the map
    socket_mutex_.lock();
    sockets_.erase(peer_address.to_string());
    socket_mutex_.unlock();
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

        // create error response
        const ServerResponse error_response(
            ServerResponseType::RequestResponse, "Error: Invalid JSON")

            send_response(error_response, peer_address.to_string());
    }

    ClientRequest* client_request;
    try {
        client_request = new ClientRequest(data);
    } catch (std::exception& e) {
        std::cout
            << "[ServerNetworkManager] Message is not a valid ClientRequest.\n"
               " Error from ClientRequest constructor: "
            << e.what()
            << "\nClientRequest was not created and reading the message "
               "aborted!"
            << std::endl;

        return ServerResponse(ServerResponseType::RequestResponse,
                              "Error: Message is not a valid ClientRequest")
            .to_string();
    }

    // Create a player id for this connection if it is a join request
    // Also add the player to a game
    if (client_request->get_type() == ClientRequestType::ClientJoinRequest) {
        Player* player_ptr =
            RequestHandler::handle_join_request(client_request, peer_address);

        if (player_ptr != nullptr) {
            player_addr_mutex_.lock();
            player_addresses_.emplace(new_player_id, peer_address.to_string());
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
        return ServerResponse(
                   ServerResponseType::RequestResponse,
                   client_request->get_type(), "", player_id,
                   "Error: Player is not a known player of this game")
            .to_string();
    }

    ResquestHandler::handle_request(client_request);
}
