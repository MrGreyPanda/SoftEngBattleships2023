#pragma once

#include <functional>
#include <shared_mutex>
#include <unordered_map>

#include "client_request.h"
#include "server_response.h"
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
    static void start_();

    /**
     * @brief Handle the messages of a new thread
     *
     * @param socket The socket to handle
     */
    static void handle_socket_(sockpp::tcp_socket socket);

    /**
     * @brief Handles an incoming message from a client
     *
     * @param message The message to handle
     * @param peer_addres The address of the client
     *
     * @return The response string to send back to the client
     */
    static std::string handle_incoming_message_(
        const std::string& message, const sockpp::inet_address& peer_address);

    /**
     * @brief Handle a join request
     *
     * @param request The client request object pointer
     * @param socket The socket the request came from
     */
    static ServerResponse handle_join_request_(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    static ServerResponse handle_ready_request_(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    static ServerResponse handle_prepared_request_(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    static ServerResponse handle_shoot_request_(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    static ServerResponse handle_give_up_request_(
        const ClientRequest* request,
        const sockpp::inet_address& peer_address);

    /**
     * @brief The mutex to lock when accessing the acceptor
     */
    static std::shared_mutex mutex_;

    /**
     * @brief The acceptor to listen for new connections
     */
    static sockpp::tcp_acceptor acceptor_;

    /**
     * @brief A map of player ids to their addresses
     */
    static std::unordered_map<std::string, std::string> player_addresses_;

    /**
     * @brief A map of player ids to their sockets
     */
    static std::unordered_map<std::string, sockpp::tcp_socket> sockets_;
};