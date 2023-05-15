#pragma once

#include <functional>
#include <shared_mutex>
#include <unordered_map>

#include "sockpp/tcp_acceptor.h"
#include "sockpp/tcp_socket.h"

class ServerNetworkManager {
   public:
    /**
     * @brief Starts the server listener loop
     */
    static void start(unsigned port = 1337);

    /**
     * @brief Stops the server listener loop
     * Stops all sockets and threads and close the acceptor
     */
    static void stop();

    /**
     * @brief Sends a response to a player
     * @param response The ServerResponse object with the information to send
     * @param player_id The id of the player to send the response to
     */
    static void send_response(const std::string& response_str,
                              const std::string& player_id);

   private:
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
        const std::string& response_str,
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
    static std::unordered_map<std::string, sockpp::inet_address>
        player_addresses_;

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