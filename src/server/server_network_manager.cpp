
#include "server_network_manager.h"

#include <nlohmann/json.hpp>
#include <thread>

#include "../common/game_state/include/player.h"
#include "../common/helpers/helper_functions.h"
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

            // create thread to handle incoming messages
            std::thread listener(_handle_socket, std::ref(socket));

            // Detach the thread so it can run in the background
            listener.detach();
        }
    }
}

void ServerNetworkManager::_handle_socket(sockpp::tcp_socket& socket) {
    //  handle incoming messages
    ssize_t msg_length;
    char msg_buffer[512];

    while ((msg_length = socket.read(msg_buffer, sizeof(msg_buffer))) > 0) {
        try {
            std::string message(msg_buffer, msg_length);
            _handle_incoming_message(message, socket);
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
    const std::string& message, sockpp::tcp_socket& socket) {
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
    if (client_request->get_type() == ClientRequestType::ClientJoinRequest) {
        _handle_join_request(client_request, socket);
        return;
    }

    // check if this is a message from a known player
    std::string player_id = client_request->get_player_id();

    if (_player_addresses.find(player_id) == _player_addresses.end()) {
        // This is not a message from a known player
        std::cout << "[ServerNetworkManager] Error: Player with ID '"
                  << player_id << "' is not a known player of this game."
                  << std::endl;
        return;
    }

    if (client_request->get_type() == ClientRequestType::ClientReadyRequest) {
        _handle_ready_request(client_request, socket);
    } else if (client_request->get_type() ==
               ClientRequestType::ClientPreparedRequest) {
        _handle_prepared_request(client_request, socket);
    } else if (client_request->get_type() ==
               ClientRequestType::ClientShootRequest) {
        _handle_shoot_request(client_request, socket);
    } else if (client_request->get_type() ==
               ClientRequestType::ClientGiveUpRequest) {
        _handle_give_up_request(client_request, socket);
    } else {
        throw std::runtime_error(
            "[ServerNetworkManager] Unhandled ClientRequest type");
    }
}

void ServerNetworkManager::_send_response(const ServerResponse& response,
                                          sockpp::tcp_socket& socket) {
    const std::string response_str = response.to_json().dump();
    socket.write(response_str.c_str(), response_str.length());
}

void ServerNetworkManager::_handle_join_request(
    const ClientRequest* client_request, sockpp::tcp_socket& socket) {
    assert(client_request->get_type() == ClientRequestType::ClientJoinRequest);

    std::cout << "[ServerNetworkManager] (Debug) Received join request from "
              << socket.peer_address().to_string() << std::endl;

    // create a player id string by creating a random hash string
    std::string new_player_id = HelperFunctions::create_random_id();

    _mutex.lock();
    _player_addresses.emplace(new_player_id,
                              socket.peer_address().to_string());
    _mutex.unlock();

    std::cout << "[ServerNetworkManager] Created player with ID '"
              << new_player_id << "' for '" << socket.peer_address() << "'"
              << std::endl;

    // create new player object
    Player* new_player = new Player(new_player_id);

    // add new player to player manager
    PlayerManager::add_or_get_player(new_player_id, new_player);

    // add the player to a game
    GameInstance* game;
    if (!GameInstanceManager::add_player_to_any_game(new_player, game)) {
        // Error adding player to a game
        std::cout << "[ServerNetworkManager] Could not add player to any game!"
                  << std::endl;
        // TODO add more error messages
    }

    // formulate response
    const ServerResponse response =
        ServerResponse(ServerResponseType::RequestResponse, game->get_id());

    // send the serialized response to the client
    _send_response(response, socket);
}

void ServerNetworkManager::_handle_ready_request(
    const ClientRequest* client_request, sockpp::tcp_socket& socket) {
    assert(client_request->get_type() ==
           ClientRequestType::ClientReadyRequest);

    std::cout << "[ServerNetworkManager] (Debug) Received ready request from "
              << socket.peer_address().to_string() << std::endl;
}

void ServerNetworkManager::_handle_prepared_request(
    const ClientRequest* client_request, sockpp::tcp_socket& socket) {
    assert(client_request->get_type() ==
           ClientRequestType::ClientPreparedRequest);

    std::cout
        << "[ServerNetworkManager] (Debug) Received perpared request from "
        << socket.peer_address().to_string() << std::endl;
}

void ServerNetworkManager::_handle_shoot_request(
    const ClientRequest* client_request, sockpp::tcp_socket& socket) {
    throw std::runtime_error("Not implemented yet");
}

void ServerNetworkManager::_handle_give_up_request(
    const ClientRequest* client_request, sockpp::tcp_socket& socket) {
    throw std::runtime_error("Not implemented yet");
}