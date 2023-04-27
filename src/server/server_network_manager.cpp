
#include "server_network_manager.h"

#include <nlohmann/json.hpp>
#include <thread>

#include "../common/game_state/include/player.h"
#include "../common/network/requests/client_request.h"
#include "game_instance_manager.h"
#include "player_manager.h"

using json = nlohmann::json;

// Declare the static variables to allocate them
std::shared_mutex ServerNetworkManager::_mutex;
sockpp::tcp_acceptor ServerNetworkManager::_acceptor;
std::unordered_map<std::string, std::string>
    ServerNetworkManager::_player_addresses;

ServerNetworkManager::ServerNetworkManager(unsigned port) {
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

    throw std::runtime_error("Not implemented");
}

void ServerNetworkManager::player_left(const std::string& player_id) {
    // TODO

    throw std::runtime_error("Not implemented");
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

            // thread to handle incoming messages
            std::thread listener(_handle_socket, std::move(socket));

            // Detach the thread so it can run in the background
            listener.detach();
        }
    }
}

void ServerNetworkManager::_handle_socket(sockpp::tcp_socket socket) {
    //  handle incoming messages
    ssize_t msg_length;
    char msg_buffer[512];

    while ((msg_length = socket.read(msg_buffer, sizeof(msg_buffer))) > 0) {
        try {
            std::string message(msg_buffer, msg_length);
            _handle_incoming_message(message, socket.peer_address());
        } catch (std::exception& err) {
            std::cerr
                << "[ServerNetworkManager] Error handling socket message: "
                << err.what() << std::endl;
        }
    }

    std::cout << "[ServerNetworkManager] Closing connection to "
              << socket.peer_address() << std::endl;
    socket.shutdown();
}

void ServerNetworkManager::_handle_incoming_message(
    const std::string& message,
    const sockpp::tcp_socket::addr_t peer_address) {
    // try to parse the message as JSON and create a client request object
    json data;
    try {
        data = json::parse(message);
    } catch (json::parse_error& e) {
        std::cout << "[ServerNetworkManager] JSON parse error: " << e.what()
                  << std::endl;
        return;
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
        return;
    }

    // Create a player id for this connection if it is a join request
    // Also add the player to a game
    if (client_request->get_type() == ClientJoinRequest) {
        std::cout << "[ServerNetworkManager] Received join request from "
                  << peer_address.to_string() << std::endl;

        // create a player id string by creating a random hash string
        std::string new_player_id =
            std::to_string(std::hash<std::string>{}(std::to_string(rand())));

        _mutex.lock();
        _player_addresses.emplace(new_player_id, peer_address.to_string());
        _mutex.unlock();

        std::cout << "[ServerNetworkManager] Created player with ID '"
                  << new_player_id << "' for '" << peer_address << "'"
                  << std::endl;

        // create new player object
        // Player* new_player = new Player(new_player_id);

        // add new player to player manager
        // PlayerManager::add_or_get_player(new_player_id, new_player);

        // add the player to a game
        // GameInstanceManager::add_player_to_any_game(new_player);

        return;
    }

    // check if this is a message from a player
    std::string player_id = client_request->get_player_id();

    if (_player_addresses.find(player_id) == _player_addresses.end()) {
        // This is not a message from a known player
        std::cout << "[ServerNetworkManager] Error: Player with ID '"
                  << player_id << "' is not a known player of this game."
                  << std::endl;
        return;
    }

    // execute client request

    // formulate a JSON response

    // serialize the JSON response to a string

    // send the response to the client
}

void ServerNetworkManager::_send_message_to_player(
    const std::string& message, const std::string& player_id) {
    // TODO

    throw std::runtime_error("Not implemented");
}