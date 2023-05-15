

#include "server_network_manager.h"

#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>

#include "request_handler.h"

using json = nlohmann::json;

// Declare the static variables to allocate them

sockpp::tcp_acceptor ServerNetworkManager::acceptor_;

std::thread listener_thread_;

std::shared_mutex ServerNetworkManager::player_addr_mutex_;

std::unordered_map<std::string, sockpp::inet_address>
    ServerNetworkManager::player_addresses_;

std::shared_mutex ServerNetworkManager::sockets_mutex_;

std::unordered_map<std::string, sockpp::tcp_socket>
    ServerNetworkManager::sockets_;

// ServerNetworkManager methods

void ServerNetworkManager::start(unsigned port) {
    if (acceptor_ && acceptor_.is_open()) {
        std::cerr << "[ServerNetworkManager] (Debug) acceptor already open"
                  << std::endl;
        return;
    } else {
        // Create the acceptor
        acceptor_ = sockpp::tcp_acceptor(port);

        if (!acceptor_) {
            std::cerr << "[ServerNetworkManager] Error creating acceptor: "
                      << acceptor_.last_error_str() << std::endl;
            return;
        }
    }

    // Start the listener loop
    std::cout << "[ServerNetworkManager] Listening on port " << port
              << std::endl;

    while (acceptor_.is_open()) {
        sockpp::inet_address peer_address;
        sockpp::tcp_socket socket = acceptor_.accept(&peer_address);
        std::cout << "[ServerNetworkManager] Received connection from "
                  << peer_address.to_string() << std::endl;

        if (!socket) {
            if (!acceptor_.is_open()) {
                // the acceptor was closed, exit the loop
                break;
            } else {
                std::cerr
                    << "[ServerNetworkManager] Error accepting connection: "
                    << socket.last_error_str() << std::endl;
                continue;
            }
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

void ServerNetworkManager::stop() {
    std::cout << "[ServerNetworkManager] Stopping server..." << std::endl;

    // Close all sockets
    for (auto& socket_pair : sockets_) {
        socket_pair.second.close();
    }

    // Close the acceptor
    acceptor_.close();

    std::cout << "[ServerNetworkManager] Server stopped" << std::endl;
}

void ServerNetworkManager::send_response(const ServerResponse& response,
                                         const std::string& player_id) {
    // Get the IP address of the player
    auto player_address_it = player_addresses_.find(player_id);

    if (player_address_it == player_addresses_.end()) {
        std::cerr << "[ServerNetworkManager] Error sending response: "
                  << "Player with ID '" << player_id << "' not found!"
                  << std::endl;
        return;
    }

    send_response_to_peer_(response, player_address_it->second);
}

void ServerNetworkManager::send_response_to_peer_(
    const ServerResponse& response, const sockpp::inet_address& address) {
    // Get the socket for the IP address
    auto socket_it = sockets_.find(address.to_string());

    if (socket_it == sockets_.end()) {
        std::cerr << "[ServerNetworkManager] Error sending response: "
                  << "Socket for IP " << address.to_string() << " not found!"
                  << std::endl;
        return;
    }

    // Send the response
    std::string message        = response.to_string() + '\0';
    sockpp::tcp_socket& socket = socket_it->second;

    auto bytes_sent = socket.write(message.c_str(), message.size());

    if (bytes_sent != message.size()) {
        std::cout << "[ServerNetworkManager] Error Failed to send full "
                     "request to server"
                  << std::endl;
        std::cerr << socket.last_error_str() << std::endl;
    } else {
        std::cout
            << "[ServerNetworkManager] (Debug) Sent response to client: '"
            << message << "'" << std::endl;
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
            std::stringstream str_stream;
            str_stream.write(msg_buffer, msg_length);
            std::string line;

            while (std::getline(str_stream, line, '\0')) {
                std::string message = line;
                handle_incoming_message_(message, peer_address);
            }
        } catch (std::exception& err) {
            std::cerr << "[ServerNetworkManager] Error while handling socket "
                         "message: "
                      << err.what() << std::endl;
        }
    }

    std::cout << "[ServerNetworkManager] Closing connection to "
              << socket.peer_address() << std::endl;

    // Delete the socket from the map
    sockets_mutex_.lock();
    sockets_.erase(peer_address.to_string());
    sockets_mutex_.unlock();

    std::cout
        << "[ServerNetworkManager] (Debug) Removed the socket for peer at "
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

        send_response_to_peer_(error_response, peer_address);
        return;
    }

    const ClientRequestType request_type =
        ClientRequest::get_client_request_type_from_message_type_string(
            data["message_type"]);

    if (request_type == ClientRequestType::Join) {
        // Handle join request

        ClientRequest client_join_request;

        try {
            client_join_request = ClientRequest(data);
        } catch (std::exception& e) {
            std::cout << "[ServerNetworkManager] Error parsing join request: "
                      << e.what() << std::endl;
            return;
        }

        // Create a player id for this connection if it is a join request
        // Also add the player to a game
        if (client_join_request.get_type() == ClientRequestType::Join) {
            std::tuple<Player*, ServerResponse> join_req_tuple =
                RequestHandler::handle_join_request(client_join_request);

            Player* player_ptr      = std::get<0>(join_req_tuple);
            ServerResponse response = std::get<1>(join_req_tuple);

            if (player_ptr != nullptr) {
                player_addr_mutex_.lock();
                // TODO check if player_ptr has ID maybe?
                player_addresses_.emplace(player_ptr->get_id(), peer_address);
                player_addr_mutex_.unlock();
            }

            send_response_to_peer_(response, peer_address);
            return;
        }
    } else {
        // Handle other requests than join
        ClientRequest client_request;
        try {
            client_request = ClientRequest(data);
        } catch (std::exception& e) {
            std::cout << "[ServerNetworkManager] Error parsing join request: "
                      << e.what() << std::endl;
            return;
        }

        // check if this is a message from a known player
        std::string player_id = client_request.get_player_id();

        // look for the IP address for the given player_id in the
        // player_addresses map
        auto player_address_it = player_addresses_.find(player_id);

        if (player_address_it == player_addresses_.end()) {
            // This is not a message from a known player
            std::cout << "[ServerNetworkManager] Error: Player with ID '"
                      << player_id << "' is not a known player of this game."
                      << std::endl;

            // create error response
            const ServerResponse response(
                ServerResponseType::RequestResponse, client_request.get_type(),
                "", player_id,
                "Error: Player is not a known player of this game");

            send_response_to_peer_(response, peer_address);
            return;
        }

        // check if the player id in the client request matches the one we
        // saved for the ip
        if (player_address_it->second != peer_address) {
            std::cout << "Error! The player ID passed does not match the IP "
                         "address stored for this player id. "
                         "Only one player per peer is currently supported!"
                      << std::endl;

            const ServerResponse response(
                ServerResponseType::RequestResponse, client_request.get_type(),
                "", player_id,
                "Error! The player ID passed does not match the IP "
                "address stored for this player id. "
                "Only one player per peer is currently supported!");

            send_response_to_peer_(response, peer_address);
            return;
        }

        RequestHandler::handle_request(client_request.get_type(), data);
    }
}
