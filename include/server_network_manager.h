#pragma once

#include <functional>
#include <shared_mutex>
#include <unordered_map>

#include "../common/network/requests/client_request.h"
#include "../common/network/responses/server_response.h"
#include "sockpp/tcp_acceptor.h"
#include "sockpp/tcp_socket.h"

class ServerNetworkManager {
   public:
    /**
     * @brief Constructs a new ServerNetworkManager
     *
     * @param port The port to listen on
     */
    ServerNetworkManager(unsigned port = 1337);
    // TODO check if we need a destructor

    /**
     * @brief Broadcasts a message to all connected clients
     *
     * @param message The message to broadcast
     */
    static void broadcast(const std::string& message);

    /**
     * // TODO
     */
    static void player_left(const std::string& player_id);

   private:
    /**
     * @brief Starts the server listener loop
     */
    static void _start();

    /**
     * @brief Handle the messages of a new thread
     *
     * @param socket The socket to handle
     */
    static void _handle_socket(sockpp::tcp_socket socket);

    /**
     * @brief Handles an incoming message from a client
     *
     * @param message The message to handle
     * @param peer_addres The address of the client
     *
     * @return The response string to send back to the client
     */
    static std::string _handle_incoming_message(
        const std::string& message, const sockpp::inet_address& peer_address);

    /**
     * @brief Handle a join request
     *
     * @param request The client request object pointer
     * @param socket The socket the request came from
     */
    static ServerResponse _handle_join_request(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    static ServerResponse _handle_ready_request(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    static ServerResponse _handle_prepared_request(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    static ServerResponse _handle_shoot_request(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    static ServerResponse _handle_give_up_request(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    /**
     * @brief The mutex to lock when accessing the acceptor
     */
    static std::shared_mutex _mutex;

    /**
     * @brief The acceptor to listen for new connections
     */
    static sockpp::tcp_acceptor _acceptor;

    /**
     * @brief A map of player ids to their addresses
     */
    static std::unordered_map<std::string, std::string> _player_addresses;

    /**
     * @brief A map of player ids to their sockets
     */
    static std::unordered_map<std::string, sockpp::tcp_socket> _sockets;
};