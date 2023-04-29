
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
    const sockpp::inet_address peer_address = socket.peer_address();
    std::string response_str;

    while ((msg_length = socket.read(msg_buffer, sizeof(msg_buffer))) > 0) {
        try {
            std::string message(msg_buffer, msg_length);
            response_str = _handle_incoming_message(message, peer_address);
            socket.write(response_str.c_str(), response_str.length());
        } catch (std::exception& err) {
            std::cerr
                << "[ServerNetworkManager] Error handling socket message: "
                << err.what() << std::endl;
        }
    }

    std::cout << "[ServerNetworkManager] Closing connection to "
              << socket.peer_address() << std::endl;
}

std::string ServerNetworkManager::_handle_incoming_message(
    const std::string& message, const sockpp::inet_address& peer_address) {
    // try to parse the message as JSON and create a client request object
    json data;
    try {
        data = json::parse(message);
    } catch (json::parse_error& e) {
        std::cout << "[ServerNetworkManager] JSON parse error: " << e.what()
                  << std::endl;
        return ServerResponse(ServerResponseType::RequestResponse,
                              "Error: Invalid JSON")
            .to_string();
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
        return _handle_join_request(client_request, peer_address).to_string();
    }

    // check if this is a message from a known player
    std::string player_id = client_request->get_player_id();

    if (_player_addresses.find(player_id) == _player_addresses.end()) {
        // This is not a message from a known player
        std::cout << "[ServerNetworkManager] Error: Player with ID '"
                  << player_id << "' is not a known player of this game."
                  << std::endl;
        return ServerResponse(
                   ServerResponseType::RequestResponse,
                   client_request->get_type(), "", player_id,
                   "Error: Player is not a known player of this game")
            .to_string();
    }

    if (client_request->get_type() == ClientRequestType::ClientReadyRequest) {
        return _handle_ready_request(client_request, peer_address).to_string();
    } else if (client_request->get_type() ==
               ClientRequestType::ClientPreparedRequest) {
        return _handle_prepared_request(client_request, peer_address)
            .to_string();
    } else if (client_request->get_type() ==
               ClientRequestType::ClientShootRequest) {
        return _handle_shoot_request(client_request, peer_address).to_string();
    } else if (client_request->get_type() ==
               ClientRequestType::ClientGiveUpRequest) {
        return _handle_give_up_request(client_request, peer_address)
            .to_string();
    } else {
        throw std::runtime_error(
            "[ServerNetworkManager] Unhandled ClientRequest type");
    }
}

ServerResponse ServerNetworkManager::_handle_join_request(
    const ClientRequest* client_request,
    const sockpp::inet_address& peer_address) {
    assert(client_request->get_type() == ClientRequestType::ClientJoinRequest);

    std::cout << "[ServerNetworkManager] Received join request from "
              << peer_address.to_string() << std::endl;

    // create a player id string by creating a random hash string
    std::string new_player_id = HelperFunctions::create_random_id();

    _mutex.lock();
    _player_addresses.emplace(new_player_id, peer_address.to_string());
    _mutex.unlock();

    std::cout << "[ServerNetworkManager] Created player with ID '"
              << new_player_id << "' for '" << peer_address << "'"
              << std::endl;

    // create new player object
    Player* new_player = new Player(new_player_id);
    std::cout << "[ServerNetworkManager] (Debug) Created new Player object"
              << std::endl;

    // add new player to player manager
    PlayerManager::add_or_get_player(new_player_id, new_player);
    std::cout << "[ServerNetworkManager] (Debug) Added Player object to "
                 "PlayerManager"
              << std::endl;

    // add the player to a game
    GameInstance* game = nullptr;
    if (GameInstanceManager::add_player_to_any_game(new_player, game)) {
        std::cout << "[ServerNetworkManager] Added Player to game with ID '"
                  << game->get_id() << "'" << std::endl;

        // formulate response
        return ServerResponse(ServerResponseType::RequestResponse,
                              ClientRequestType::ClientJoinRequest,
                              game->get_id(), new_player_id);
    } else {
        // Error adding player to a game
        std::cout << "[ServerNetworkManager] Error: Could not add player to "
                     "any game!"
                  << std::endl;
        // TODO add more error messages

        // Formulate error response message
        return ServerResponse(ServerResponseType::RequestResponse,
                              ClientRequestType::ClientJoinRequest, "",
                              new_player_id,
                              "Error: Could not add player to any game!");
    }
}

ServerResponse ServerNetworkManager::_handle_ready_request(
    const ClientRequest* client_request,
    const sockpp::inet_address& peer_address) {
    assert(client_request->get_type() ==
           ClientRequestType::ClientReadyRequest);

    std::cout << "[ServerNetworkManager] (Debug) Received ready request from "
              << peer_address.to_string() << std::endl;

    return ServerResponse(ServerResponseType::RequestResponse,
                          ClientRequestType::ClientReadyRequest,
                          client_request->get_game_id(),
                          client_request->get_player_id());
}

ServerResponse ServerNetworkManager::_handle_prepared_request(
    const ClientRequest* client_request,
    const sockpp::inet_address& peer_address) {
    assert(client_request->get_type() ==
           ClientRequestType::ClientPreparedRequest);

    std::cout
        << "[ServerNetworkManager] (Debug) Received perpared request from "
        << peer_address.to_string() << std::endl;

    return ServerResponse(ServerResponseType::RequestResponse,
                          ClientRequestType::ClientPreparedRequest,
                          client_request->get_game_id(),
                          client_request->get_player_id());
}

ServerResponse ServerNetworkManager::_handle_shoot_request(
    const ClientRequest* client_request,
    const sockpp::inet_address& peer_address) {
    throw std::runtime_error("Not implemented yet");
}

ServerResponse ServerNetworkManager::_handle_give_up_request(
    const ClientRequest* client_request,
    const sockpp::inet_address& peer_address) {
    throw std::runtime_error("Not implemented yet");
}