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
     * @brief Sends a response to a player
     * @param response The ServerResponse object with the information to send
     * @param player_id The id of the player to send the response to
     */
    static void send_response(const ServerResponse& response,
                              const std::string& player_id);

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
     */
    static void handle_incoming_message_(
        const std::string& message, const sockpp::inet_address& peer_address);

    /**
     * @brief Sends a response to a peer
     *
     * @param response The ServerResponse object with the information to send
     * @param peer_address The address of the peer to send the response to
     */
    static void send_response_to_peer_(
        const ServerResponse& response,
        const sockpp::inet_address& peer_address);

    /**
     * @brief The acceptor to listen for new connections
     */
    static sockpp::tcp_acceptor acceptor_;

    /**
     * @brief The mutex to lock when accessing the player_addresses map
     */
    static std::shared_mutex player_addr_mutex_;

    /**
     * @brief A map of player ids to their addresses
     */
    static std::unordered_map<std::string, std::string> player_addresses_;

    /**
     * @brief The mutex to lock when accessing the sockets map
     *
     */
    static std::shared_mutex sockets_mutex_;

    /**
     * @brief A map of internet addresses to sockets
     */
    static std::unordered_map<std::string, sockpp::tcp_socket> sockets_;
};